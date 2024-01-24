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

#define MINPORT 49152
#define MAXPORT 65535
#define PWD_LEN 4
#define PENDING_QUEUE_SIZE 10
#define MAX_CLIENTS 100
#define EVENTLIST_SIZE 10
#define SEVER_WAIT_TIME 10

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

  void acceptClient(std::vector<struct kevent> eventVec);
  void handleEvent(struct kevent* eventlist, int eventCount,
                   std::vector<struct kevent> eventVec);

  void enrollEventToVec(std::vector<struct kevent> eventVec, uintptr_t ident,
                        int16_t filter, uint16_t flags, uint32_t fflags,
                        intptr_t data, void* udata);

 public:
  Server(int ac, char** av);
  ~Server();

  void run();
};

#endif