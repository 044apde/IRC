#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

class ClientSocket {
 private:
  int clientFd;

  ClientSocket();
  ClientSocket(const ClientSocket& obj);
  ClientSocket& operator=(const ClientSocket& obj);

 public:
  ClientSocket(int clientFd);
  ~ClientSocket();

  int getClientFd();
};

#endif