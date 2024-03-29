#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../command_invoker/CommandInvoker.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../param/token_param/TokenParam.hpp"
#include "../signal/signal.hpp"

#define MINPORT 1024
#define MAXPORT 65535
#define PWD_LEN 4
#define PENDING_QUEUE_SIZE 10
#define MAX_CLIENTS 100
#define EVENTLIST_SIZE 10
#define SEVER_WAIT_TIME 10
#define MESSAGE_MAX_LENGTH 512

class CommandInvoker;

class Server {
 private:
  ServerParam serverParam;
  CommandInvoker commandInvoker;

  Server(const Server& obj);
  void sendCommand(int targetFd);
  int makeServerListening(int serverPort);
  int parseServerPort(char* portNum);
  std::string parseServerPwd(char* pwdNum);
  int makeKqueueFd();
  void acceptClient(std::vector<struct kevent>& eventVec);
  void handleEvent(struct kevent* eventlist, int eventCount,
                   std::vector<struct kevent>& eventVec);
  void enrollEventToVec(std::vector<struct kevent>& eventVec, uintptr_t ident,
                        int16_t filter, uint16_t flags, uint32_t fflags,
                        intptr_t data, void* udata);
  void manageRequest(int targetFd, std::vector<struct kevent>& eventvec);
  std::string getMessage(int clientSocket);
  void disconnectClient(int clientSocket, std::vector<struct kevent>& eventvec);
  void handleCombindBuffer(std::string combinedBuffer, int clientSocket,
                           std::vector<struct kevent>& eventvec);
  std::string makePrefix(std::string& clientMesaage);
  std::string makeCommand(std::string& clientMessage);
  std::vector<std::string> makeParams(std::string clientMessage);
  std::string makeCombinedBuffer(std::string clientMessage, int targetFD);
  void setClientReplyMessage(CommandResponseParam cmdResParam,
                             std::vector<struct kevent>& eventvec,
                             int clientSocket);

 public:
  Server& operator=(const Server& obj);
  Server();
  Server(int ac, char** av);
  ~Server();

  ServerParam& getServerParam();
  void run();
};

extern Server server;

#endif