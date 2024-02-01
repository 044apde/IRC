#include "Client.hpp"

Client::Client() : clientFd(-1), isCheckPass(false) {}

Client::Client(const int& clientFd) : clientFd(clientFd), isCheckPass(false) {}

Client::~Client() {}

Client::Client(const Client& other) : clientFd(other.clientFd) {
  *this = other;
}

Client& Client::operator=(const Client& other) {
  if (this != &other) {
    this->isCheckPass = other.isCheckPass;
    this->nickname = other.nickname;
    this->username = other.username;
    this->host = other.host;
    this->channelSet = other.channelSet;
    this->remainRequestBuffer = other.remainRequestBuffer;
  }
  return *this;
}

const int& Client::getClientFd() const { return this->clientFd; }

const bool& Client::getIsCheckPass() const { return this->isCheckPass; }

const std::string& Client::getNickname() const { return this->nickname; }

const std::string& Client::getUsername() const { return this->username; }

const std::string& Client::getHost() const { return this->host; }

void Client::setIsCheckPassTrue() {
  this->isCheckPass = true;
  return;
}

void Client::setNickname(const std::string& nickname) {
  this->nickname = nickname;
  return;
}

void Client::setUsername(const std::string& username) {
  this->username = username;
  return;
}

void Client::setHost(const std::string& host) {
  this->host = host;
  return;
}

void Client::addChannel(Channel* channel) {
  this->channelSet.insert(channel);
  return;
}

void Client::removeChannel(Channel* channel) {
  this->channelSet.erase(channel);
  return;
}

void Client::removeAllChannel() {
  this->channelSet.clear();
  return;
}

size_t Client::getChannelSetSize() { return this->channelSet.size(); }

void Client::pushRemainRequestBuffer(const std::string& remainRequestBuffer) {
  this->remainRequestBuffer += remainRequestBuffer;
  return;
}

const std::string Client::popRemainRequestBuffer() {
  std::string tempRemainRequestBuffer = this->remainRequestBuffer;

  this->remainRequestBuffer.clear();
  return tempRemainRequestBuffer;
}

const std::set<const int> Client::getAllChannelClientFd() const {
  std::set<const int> allChannelClientFdSet;

  for (std::set<Channel*>::iterator it = this->channelSet.begin();
       it != this->channelSet.end(); ++it) {
    (*it)->setAllClientFd(allChannelClientFdSet);
  }
  return allChannelClientFdSet;
}

std::vector<std::string> Client::popReplyMessages() {
  std::vector<std::string> result;

  result = this->replyMessages;
  this->replyMessages.clear();
  return result;
}

void Client::pushReplyMessages(std::string replyMessage) {
  this->replyMessages.push_back(replyMessage);
  return;
}
