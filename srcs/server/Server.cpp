#include "Server.hpp"

Server::Server() { return; }

Server::Server(const Server& obj) {
  if (this == &obj)
    return;
  else {
    // serverParam commandInvoker 객체 초기화 필요
  };
  return;
}

Server& Server::operator=(const Server& obj) {
  if (this == &obj)
    return *this;
  else {
    // serverParam commandInvoker 객체 초기화 필요
  }
  return *this;
}

void Server::checkServerPort(char* portNum) {
  std::istringstream iss(portNum);
  unsigned long temp;

  if ((iss >> temp) == false)
    throw std::runtime_error("포트를 변환하는떼 실패했습니다.");
  if (temp < MINPORT || temp > MAXPORT)
    throw std::runtime_error("유효한 포트 범위는 49152 ~ 65535입니다.");
  return;
}

void Server::setServerPwd(char* pwdNum) {
  size_t pwdNumLen = strlen(pwdNum);
  if (PWDLEN != 4)
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

    checkServerPort(av[1]);
    std::string serverPwd = setServerPwd(av[2]);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    exit(1);
  }
  return;
}

Server::~Server() { return; }