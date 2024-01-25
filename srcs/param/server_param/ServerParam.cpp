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

void ServerParam::addNewClient(const int& clientFd) {
  assert(clientFd > 2);
  assert(this->clientMap.find(clientFd) == this->clientMap.end());
  this->clientMap.insert(std::make_pair(clientFd, new Client(clientFd)));
  return;
}

void ServerParam::addNewChannel(const std::string& channelName,
                                Client* firstClient) {
  assert(channelName.empty() == false);
  assert(this->channelMap.find(channelName) == this->channelMap.end());
  Channel* channel = new Channel(channelName);
  this->channelMap.insert(std::make_pair(channelName, channel));
  firstClient->addChannel(channel);
  channel->addClient(firstClient);
  return;
}

void ServerParam::removeClient(const int& clientFd) {
  std::map<int, Client*>::iterator it = this->clientMap.find(clientFd);
  assert(clientFd > 2);
  assert(it != this->clientMap.end());
  it->second->removeAllChannel();
  delete it->second;
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

Client* ServerParam::getClientByNickname(const std::string& nickname) const {
  assert(nickname.empty() == false);
  for (std::map<int, Client*>::const_iterator it = this->clientMap.begin();
       it != this->clientMap.end(); ++it) {
    if (it->second->getNickname() == nickname) {
      return it->second;
    }
  }
  return NULL;
}

Channel* ServerParam::getChannel(const std::string& channelName) const {
  assert(channelName.empty() == false);
  assert(this->channelMap.find(channelName) != this->channelMap.end());
  return this->channelMap.find(channelName)->second;
}

void ServerParam::addClientAndChannelEachOther(Client* client,
                                               Channel* channel) {
  assert(client != NULL);
  assert(channel != NULL);
  client->addChannel(channel);
  channel->addClient(client);
  return;
}

void ServerParam::removeClientAndChannelEachOther(Client* client,
                                                  Channel* channel) {
  assert(client != NULL);
  assert(channel != NULL);
  client->removeChannel(channel);
  channel->removeClient(client);
  return;
}
