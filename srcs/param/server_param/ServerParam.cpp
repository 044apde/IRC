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
  addClientAndChannelEachOther(firstClient, channel);
  return;
}

void ServerParam::removeClient(const int& clientFd) {
  assert(clientFd > 2);
  std::map<int, Client*>::iterator clientIt = this->clientMap.find(clientFd);
  if (clientIt == this->clientMap.end()) {
    return;
  }
  std::vector<std::string> deletedChannelNameVec;
  for (std::map<std::string, Channel*>::iterator channelIt =
           this->channelMap.begin();
       channelIt != this->channelMap.end(); channelIt++) {
    if (channelIt->second->getClientMap().find(clientIt->second) !=
        channelIt->second->getClientMap().end()) {
      channelIt->second->removeClient(clientIt->second);
    }
    if (channelIt->second->getUserCountInChannel() == 0) {
      std::string channelName = channelIt->first;
      if (removeChannel(channelIt->first) == true) {
        deletedChannelNameVec.push_back(channelName);
      }
    }
  }
  for (size_t i = 0; i < deletedChannelNameVec.size(); i++) {
    this->channelMap.erase(deletedChannelNameVec[i]);
  }
  clientIt->second->removeAllChannel();
  delete clientIt->second;
  clientIt->second = NULL;
  this->clientMap.erase(clientFd);
  return;
}

bool ServerParam::removeChannel(const std::string channelName) {
  assert(channelName.empty() == false);
  std::map<std::string, Channel*>::iterator it =
      this->channelMap.find(channelName);
  if (it != this->channelMap.end()) {
    std::string deletedChannelName = it->first;
    delete it->second;
    it->second = NULL;
    return true;
    // this->channelMap.erase(deletedChannelName);
  }
  return false;
}

Client* ServerParam::getClient(const int& clientFd) const {
  assert(clientFd > 2);
  std::map<int, Client*>::const_iterator it = this->clientMap.find(clientFd);
  if (it == this->clientMap.end()) {
    return NULL;
  }
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
  std::map<std::string, Channel*>::const_iterator it =
      this->channelMap.find(channelName);
  if (it == this->channelMap.end()) {
    return NULL;
  }
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
  if (channel->getUserCountInChannel() == 0) {
    Channel* deleteChannel = channel;
    this->channelMap.erase(channel->getChannelName());
    delete deleteChannel;
    deleteChannel = NULL;
  }
  return;
}
