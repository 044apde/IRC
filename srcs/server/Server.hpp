#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sstream>
#include <string>

#define MINPORT 49152
#define MAXPORT 65535
#define PWDLEN 4

class Server {
 private:
  // ServerParam serverParam;
  // CommandInvoker commandInvoker;

  // paredParam parse(std::string input);
  // void acceptClient();
  // void sendCommand(CommandResponseParam& responseParam);

  Server();
  Server(const Server& obj);
  Server& operator=(const Server& obj);

  void checkServerPort(char* portNum);
  void setServerPwd(char* pwdNum);

 public:
  Server(int ac, char** av);
  ~Server();
};

#endif