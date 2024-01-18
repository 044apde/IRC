#include "ClientSocket.hpp"

ClientSocket::ClientSocket() : clientFd(-1) { return; }

ClientSocket::ClientSocket(const ClientSocket& obj) : clientFd(obj.clientFd) {
  return;
}

ClientSocket& ClientSocket::operator=(const ClientSocket& obj) {
  if (this == &obj) return *this;
  clientFd = obj.clientFd;
  return *this;
}

ClientSocket::ClientSocket(int clientFd) {
  this->clientFd = clientFd;
  return;
}

ClientSocket::~ClientSocket() { return; }

int ClientSocket::getClientFd() { return clientFd; }