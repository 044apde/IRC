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

std::map<int, Client*> ServerParam::getClientMap() const {
  return this->clientMap;
}

std::map<std::string, Channel*> ServerParam::getChannelMap() const {
  return this->channelMap;
}
