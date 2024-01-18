#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#define LISTEN_QUEUE_SIZE 100

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstring>

#include "../parse/ServerInfo.hpp"

class ServerSocket {
 private:
  int socketFd;

  ServerSocket& operator=(const ServerSocket& obj);
  ServerSocket();
  ServerSocket(const ServerSocket& obj);
  void bindSocket(ServerInfo& serverInfo);
  void startListen();

 public:
  ServerSocket(ServerInfo& serverInfo);
  ~ServerSocket();

  int getServerSocketFD();
};

#endif