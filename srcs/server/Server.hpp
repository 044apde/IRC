#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../param/server_param/ServerParam.hpp"

// 클래스 임시 선언
class CommandInvoker;

#define MINPORT 49152
#define MAXPORT 65535
#define PWD_LEN 4
#define PENDING_QUEUE_SIZE 10
#define MAX_CLIENTS 100
#define EVENTLIST_SIZE 10
#define SEVER_WAIT_TIME 10
#define MESSAGE_MAX_LENGTH 2000

class Server {
 private:
  ServerParam serverParam;
  // CommandInvoker commandInvoker;

  // paredParam parse(std::string input);
  // void sendCommand(CommandResponseParam& responseParam);

  Server();
  Server(const Server& obj);
  Server& operator=(const Server& obj);

  int makeServerListening(int serverPort);
  int parseServerPort(char* portNum);
  std::string parseServerPwd(char* pwdNum);
  int makeKqueueFd();
  struct timespec makeTimeout();

  void acceptClient(std::vector<struct kevent>& eventVec);
  void handleEvent(struct kevent* eventlist, int eventCount,
                   std::vector<struct kevent>& eventVec);
  void enrollEventToVec(std::vector<struct kevent>& eventVec, uintptr_t ident,
                        int16_t filter, uint16_t flags, uint32_t fflags,
                        intptr_t data, void* udata);

  // 1월 25일 추가한 멤버 함수
  void manageRequest(int targetFd, std::vector<struct kevent>& eventvec,
                     struct kevent& eventlist);
  std::string getMessage(int clientSocket, struct kevent& eventlist);
  void disconnectClient(int clientSocket, std::vector<struct kevent>& eventvec);
  void tokenize(std::string clientMessage);
  std::string makePrefix(std::string& clientMesaage);
  std::string makeCommand(std::string& clientMessage);
  // std::vector<std::string> makeParams(std::string clientMessage);

 public:
  Server(int ac, char** av);
  ~Server();

  void run();
};

#endif