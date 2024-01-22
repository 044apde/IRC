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

int Server::getServerPort(char* portNum) {
  std::istringstream iss(portNum);
  unsigned long temp;

  if ((iss >> temp) == false)
    throw std::runtime_error("포트를 변환하는떼 실패했습니다.");
  if (temp < MINPORT || temp > MAXPORT)
    throw std::runtime_error("유효한 포트 범위는 49152 ~ 65535입니다.");
  return static_cast<int>(temp);
}

std::string Server::getServerPwd(char* pwdNum) {
  size_t pwdNumLen = strlen(pwdNum);
  if (pwdNumLen != PWD_LEN)
    throw std::runtime_error("비밀번호를 4자리로 설정하세요.");
  for (size_t i = 0; i < pwdNumLen; ++i) {
    if (std::isdigit(pwdNum[i]) == 0) {
      throw std::runtime_error("비밀번호는 숫자로만 구성되어야 합니다.");
    }
  }
  return pwdNum;
}

int Server::getSocket(int serverPort) {
  int serverSocket;
  struct sockaddr_in serverAddr;

  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(serverPort);

  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
      -1)
    throw std::runtime_error("서버 소캣 바인딩에 실패했습니다.");
  if (listen(serverSocket, PENDING_QUEUE_SIZE))
    throw std::runtime_error("서버 리슨에 실패했습니다.");
  return serverSocket;
}

Server::Server(int ac, char** av) {
  try {
    if (ac != 3) throw std::runtime_error("포트와 비밀번호가 필요합니다.");

    int serverPort = getServerPort(av[1]);
    std::string serverPassword = getServerPwd(av[2]);
    int serverFd = getSocket(serverPort);

    serverParam.setServerFd(serverFd);
    std::cout << "FD: " << serverFd << std::endl;
    serverParam.setServerPassword(serverPassword);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    exit(1);
  }
  return;
}

Server::~Server() { return; }