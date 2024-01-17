#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

#include <string>

class ServerInfo {
 private:
  int portNumber;
  std::string serverPwd;

  ServerInfo();
  ServerInfo(const ServerInfo& obj);
  ServerInfo& operator=(const ServerInfo& obj);

  void setPortNumber(char* portNum);
  void setServerPwd(char* pwdNum);

 public:
  ServerInfo(int ac, char** av);
  ~ServerInfo();
};

#endif