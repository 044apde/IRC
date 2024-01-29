#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <set>
#include <string>

#include "../client/Client.hpp"

class Client;

class Channel {
 private:
  const std::string channelName;
  bool isInviteOnly;
  bool isSetTopicOpOnly;
  bool isSetKey;
  bool isSetMaxUser;
  size_t maxUser;
  std::string key;
  std::string topic;
  std::map<Client*, bool> clientMap;
  std::set<Client*> invitedclientSet;
  Channel();

 public:
  Channel(const std::string& channelName);
  ~Channel();
  Channel(const Channel& other);
  Channel& operator=(const Channel& other);
  const std::string& getChannelName() const;
  void inviteClient(Client* invitedClient);
  void setInviteOnly();
  void setTopicOpOnly();
  void setKey(std::string key);
  void setMaxUser(size_t maxUser);
  void setOpClient(Client* client);
  void setTopic(const std::string& topic);
  void unsetInviteOnly();
  void unsetTopicOpOnly();
  void unsetKey();
  void unsetMaxUser();
  void unsetOpClient(Client* client);
  bool isInviteOnlyChannel();
  bool isSetTopicOpOnlyChannel();
  bool isSetKeyChannel();
  bool isKeyMatched(const std::string& key);
  bool isChannelFull();
  bool isClientInChannel(Client* client);
  bool isClientInChannelByNickname(std::string nickname);
  bool isOpClient(Client* client);
  bool isClientInvited(Client* client);
  void addClient(Client* client);
  void removeClient(Client* client);
  const std::string& getChannelKey() const;
  const std::string& getTopic() const;
  void setAllClientFd(std::set<const int>& clientFdSet);
  const std::set<const int> getAllClientFd();
  size_t getUserCountInChannel() const;
};

#endif
