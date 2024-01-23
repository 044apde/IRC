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

const int& ServerParam::getServerFd() const {
  assert(this->serverFd != -1);
  return this->serverFd;
}

const std::string& ServerParam::getServerPassword() const {
  assert(this->serverPassword.empty() == false);
  return this->serverPassword;
}

void ServerParam::addClient(const int& clientFd, Client* client) {
  assert(clientFd > 2);
  assert(this->clientMap.find(clientFd) == this->clientMap.end());
  this->clientMap.insert(std::make_pair(clientFd, client));
  return;
}

void ServerParam::addChannel(const std::string& channelName, Channel* channel) {
  assert(channelName.empty() == false);
  assert(this->channelMap.find(channelName) == this->channelMap.end());
  this->channelMap.insert(std::make_pair(channelName, channel));
  return;
}

void ServerParam::removeClient(const int& clientFd) {
  assert(clientFd > 2);
  assert(this->clientMap.find(clientFd) != this->clientMap.end());
  this->clientMap.erase(clientFd);
  return;
}

void ServerParam::removeChannel(const std::string& channelName) {
  assert(channelName.empty() == false);
  assert(this->channelMap.find(channelName) != this->channelMap.end());
  this->channelMap.erase(channelName);
  return;
}

Client* ServerParam::getClient(const int& clientFd) const {
  assert(clientFd > 2);
  assert(this->clientMap.find(clientFd) != this->clientMap.end());
  return this->clientMap.find(clientFd)->second;
}

Channel* ServerParam::getChannel(const std::string& channelName) const {
  assert(channelName.empty() == false);
  assert(this->channelMap.find(channelName) != this->channelMap.end());
  return this->channelMap.find(channelName)->second;
}
