#include "Server.hpp"

Server::Server() : portNumber(-1), serverPwd("") { return; }

Server::Server(const Server& obj) {
  if (this == &obj)
    return;
  else {
    portNumber = obj.portNumber;
    serverPwd = obj.serverPwd;
    // serverParam commandInvoker 객체 초기화 필요
  };
  return;
}

Server& Server::operator=(const Server& obj) {
  if (this == &obj)
    return *this;
  else {
    portNumber = obj.portNumber;
    serverPwd = obj.serverPwd;
    // serverParam commandInvoker 객체 초기화 필요
  }
  return *this;
}

void Server::setPortNumber(char* portNum) {
  std::istringstream iss(portNum);
  unsigned long temp;

  if ((iss >> temp) == false)
    throw std::runtime_error("포트를 변환하는떼 실패했습니다.");
  if (temp < 49152 || temp > 65535)
    throw std::runtime_error("유효한 포트 범위는 49152 ~ 65535입니다.");
  portNumber = static_cast<int>(temp);
  return;
}

void Server::setServerPwd(char* pwdNum) {
  size_t pwdNumLen = strlen(pwdNum);
  if (pwdNumLen != 4)
    throw std::runtime_error("비밀번호를 4자리로 설정하세요.");

  for (size_t i = 0; i < pwdNumLen; ++i) {
    if (std::isdigit(pwdNum[i]) == 0) {
      throw std::runtime_error("비밀번호는 숫자로만 구성되어야 합니다.");
    }
  }
  serverPwd = pwdNum;
  return;
}

Server::Server(int ac, char** av) {
  try {
    if (ac != 3) throw std::runtime_error("포트와 비밀번호가 필요합니다.");

    setPortNumber(av[1]);
    setServerPwd(av[2]);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  return;
}

Server::~Server() { return; }