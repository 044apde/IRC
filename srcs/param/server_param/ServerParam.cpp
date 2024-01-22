#include "ServerParam.hpp"

ServerParam::ServerParam() : serverFd(-1), serverPassword("") {}

ServerParam::~ServerParam() {}

ServerParam::ServerParam(const ServerParam& other) { *this = other; }

ServerParam& ServerParam::operator=(const ServerParam& other) {
  if (this != &other) {
    this->serverFd = other.serverFd;
    this->serverPassword = other.serverPassword;
    this->clientMap = other.clientMap;
    this->channelMap = other.channelMap;
  }
  return *this;
}

void ServerParam::setServerFd(const int& serverFd) {
  static bool assertChecker = false;

  assert(assertChecker == false);
  assertChecker = true;
  this->serverFd = serverFd;
}

void ServerParam::setServerPassword(const std::string& serverPassword) {
  static bool assertChecker = false;

  assert(assertChecker == false);
  assertChecker = true;
  this->serverPassword = serverPassword;
}

const int& ServerParam::getServerFd() const { return this->serverFd; }

const std::string& ServerParam::getServerPassword() const {
  return this->serverPassword;
}

bool ServerParam::addClient(const int& clientFd, Client* client) {
  if (this->clientMap.find(clientFd) != this->clientMap.end()) {
    return false;
  }
  this->clientMap[clientFd] = client;
  return true;
}

bool ServerParam::addChannel(const std::string& channelName, Channel* channel) {
  if (this->channelMap.find(channelName) != this->channelMap.end()) {
    return false;
  }
  this->channelMap[channelName] = channel;
  return true;
}

bool ServerParam::removeClient(const int& clientFd) {
  if (this->clientMap.find(clientFd) == this->clientMap.end()) {
    return false;
  }
  this->clientMap.erase(clientFd);
  return true;
}

bool ServerParam::removeChannel(const std::string& channelName) {
  if (this->channelMap.find(channelName) == this->channelMap.end()) {
    return false;
  }
  this->channelMap.erase(channelName);
  return true;
}

Client* ServerParam::getClient(const int& clientFd) const {
  if (this->clientMap.find(clientFd) == this->clientMap.end()) {
    return NULL;
  }
  return this->clientMap.at(clientFd);
}

Channel* ServerParam::getChannel(const std::string& channelName) const {
  if (this->channelMap.find(channelName) == this->channelMap.end()) {
    return NULL;
  }
  return this->channelMap.at(channelName);
}
