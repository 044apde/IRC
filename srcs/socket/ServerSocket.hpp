#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

class ServerSocket {
 private:
  int socketFd;

 public:
  ServerSocket();
  ServerSocket(const ServerSocket& obj);
  ServerSocket& operator=(const ServerSocket& obj);
  ~ServerSocket();
};

#endif