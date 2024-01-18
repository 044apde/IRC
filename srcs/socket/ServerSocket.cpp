#include "ServerSocket.hpp"

ServerSocket::ServerSocket() { return; }

ServerSocket& ServerSocket::operator=(const ServerSocket& obj) {
  if (this == &obj) return *this;
  socketFd = obj.socketFd;
  return (*this);
}

ServerSocket::ServerSocket(const ServerSocket& obj) {
  if (this == &obj) return;
  socketFd = obj.socketFd;
  return;
}

void ServerSocket::bindSocket(ServerInfo& serverInfo) {
  struct sockaddr_in serverAddr;
  socketFd = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(serverInfo.getPortNumber());

  if (bind(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    throw std::runtime_error(
        "바인드에서 문제가 생겼습니다. 다른 포트를 시도하세요.");
  return;
}

void ServerSocket::startListen() {
  if (listen(socketFd, LISTEN_QUEUE_SIZE) == -1)
    throw std::runtime_error("서버가 수신 대기하는 것을 실패했습니다.");
  return;
}

ServerSocket::ServerSocket(ServerInfo& serverInfo) {
  try {
    bindSocket(serverInfo);
    startListen();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  return;
}

ServerSocket::~ServerSocket() { return; }

int ServerSocket::getServerSocketFD() { return socketFd; }