#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <iostream>
#include <sstream>
#include <string>

#include "../param/server_param/ServerParam.hpp"

#define MINPORT 49152
#define MAXPORT 65535
#define PWD_LEN 4
#define PENDING_QUEUE_SIZE 10

class Server {
 private:
  ServerParam serverParam;
  // CommandInvoker commandInvoker;

  // paredParam parse(std::string input);
  // void acceptClient();
  // void sendCommand(CommandResponseParam& responseParam);

  Server();
  Server(const Server& obj);
  Server& operator=(const Server& obj);

  int getSocket(int serverPort);
  int getServerPort(char* portNum);
  std::string getServerPwd(char* pwdNum);

 public:
  Server(int ac, char** av);
  ServerParam& getServerParam() { return serverParam; };
  ~Server();
};

#endif