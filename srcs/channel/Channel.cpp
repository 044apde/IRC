#include "Channel.hpp"

Channel::Channel() : channelName("") {}

Channel::Channel(const std::string& channelName) : channelName(channelName) {}

Channel::~Channel() {}

Channel::Channel(const Channel& other) : channelName(other.channelName) {
  *this = other;
}

Channel& Channel::operator=(const Channel& other) {
  if (this != &other) {
    this->isInviteOnly = other.isInviteOnly;
    this->isSetTopicOpOnly = other.isSetTopicOpOnly;
    this->isSetKey = other.isSetKey;
    this->isSetMaxUser = other.isSetMaxUser;
    this->maxUser = other.maxUser;
    this->key = other.key;
    this->topic = other.topic;
    this->clientMap = other.clientMap;
    this->invitedclientSet = other.invitedclientSet;
  }
  return *this;
}

const std::string& Channel::getChannelName() const { return this->channelName; }

void Channel::inviteClient(Client* invitedClient) {
  this->invitedclientSet.insert(invitedClient);
  return;
}

void Channel::setInviteOnly() {
  this->isInviteOnly = true;
  return;
}

void Channel::setTopicOpOnly() {
  this->isSetTopicOpOnly = true;
  return;
}

void Channel::setKey(std::string key) {
  this->isSetKey = true;
  this->key = key;
  return;
}

void Channel::setMaxUser(size_t maxUser) {
  this->isSetMaxUser = true;
  this->maxUser = maxUser;
  return;
}

void Channel::setOpClient(Client* client) {
  this->clientMap[client] = true;
  return;
}

void Channel::setTopic(const std::string& topic) {
  this->topic = topic;
  return;
}

void Channel::unsetInviteOnly() {
  this->isInviteOnly = false;
  return;
}

void Channel::unsetTopicOpOnly() {
  this->isSetTopicOpOnly = false;
  return;
}

void Channel::unsetKey() {
  this->isSetKey = false;
  this->key.clear();
  return;
}

void Channel::unsetMaxUser() {
  this->isSetMaxUser = false;
  this->maxUser = 0;
  return;
}

void Channel::unsetOpClient(Client* client) {
  this->clientMap[client] = false;
  return;
}

bool Channel::isInviteOnlyChannel() { return this->isInviteOnly; }

bool Channel::isSetTopicOpOnlyChannel() { return this->isSetTopicOpOnly; }

bool Channel::isSetKeyChannel() { return this->isSetKey; }

bool Channel::isKeyMatched(const std::string& key) {
  assert(key.empty() == false);
  if (this->key == key) {
    return true;
  }
  return false;
}

bool Channel::isChannelFull() {
  if (this->isSetMaxUser == true && this->clientMap.size() >= this->maxUser) {
    return true;
  }
  return false;
}

bool Channel::isClientInChannel(Client* client) {
  if (this->clientMap.find(client) == this->clientMap.end()) {
    return false;
  }
  return true;
}

bool Channel::isClientInChannelByNickname(std::string nickname) {
  for (std::map<Client*, bool>::iterator it = this->clientMap.begin();
       it != this->clientMap.end(); it++) {
    if (it->first != NULL && it->first->getNickname() == nickname) {
      return true;
    }
  }
  return false;
}

bool Channel::isOpClient(Client* client) {
  std::map<Client*, bool>::iterator it = this->clientMap.find(client);
  if (it == this->clientMap.end()) {
    return false;
  }
  return it->second;
}

bool Channel::isClientInvited(Client* client) {
  if (this->invitedclientSet.find(client) == this->invitedclientSet.end()) {
    return false;
  }
  return true;
}

void Channel::addClient(Client* client) {
  this->clientMap.insert(
      std::make_pair(client, this->clientMap.size() == 0 ? true : false));
  if (this->invitedclientSet.find(client) != this->invitedclientSet.end()) {
    this->invitedclientSet.erase(client);
  }
  return;
}

void Channel::removeClient(Client* client) {
  if (this->clientMap.find(client) != this->clientMap.end()) {
    this->clientMap.erase(client);
  }
  if (this->invitedclientSet.find(client) != this->invitedclientSet.end()) {
    this->invitedclientSet.erase(client);
  }
  return;
}

const std::string& Channel::getChannelKey() const { return this->key; }

const std::string& Channel::getTopic() const { return this->topic; }

void Channel::setAllClientFd(std::set<const int>& clientFdSet) {
  for (std::map<Client*, bool>::iterator it = this->clientMap.begin();
       it != this->clientMap.end(); ++it) {
    if (it->first != NULL) {
      clientFdSet.insert(it->first->getClientFd());
    }
  }
  return;
}

const std::set<const int> Channel::getAllClientFd() {
  std::set<const int> clientFdSet;

  for (std::map<Client*, bool>::iterator it = this->clientMap.begin();
       it != this->clientMap.end(); ++it) {
    if (it->first != NULL) {
      clientFdSet.insert(it->first->getClientFd());
    }
  }

  return clientFdSet;
}

const size_t Channel::getUserCountInChannel() const {
  return this->clientMap.size();
}
