#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sstream>
#include <string>

class Server {
 private:
  // ServerParam serverParam;
  // CommandInvoker commandInvoker;

  // paredParam parse(std::string input);
  // void acceptClient();
  // void sendCommand(CommandResponseParam& responseParam);

  int portNumber;
  std::string serverPwd;

  Server();
  Server(const Server& obj);
  Server& operator=(const Server& obj);

  void setPortNumber(char* portNum);
  void setServerPwd(char* pwdNum);

 public:
  Server(int ac, char** av);
  ~Server();
};

#endif