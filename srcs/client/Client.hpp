#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <set>
#include <string>

#include "../channel/Channel.hpp"

class Channel;

class Client {
 private:
  int clientFd;
  bool isCheckPass;
  std::string nickname;
  std::string username;
  std::string host;
  std::set<Channel*> channelSet;
  std::string remainRequestBuffer;
  Client();

 public:
  Client(const int& clientFd);
  ~Client();
  Client(const Client& other);
  Client& operator=(const Client& other);
  const int& getClientFd() const;
  const bool& getIsCheckPass() const;
  const std::string& getNickname() const;
  const std::string& getUsername() const;
  const std::string& getHost() const;
  std::set<Channel*>& getChannelSet();
  void setIsCheckPassTrue();
  void setNickname(const std::string& nickname);
  void setUsername(const std::string& username);
  void setHost(const std::string& host);
  void addChannel(Channel* channel);
  void removeChannel(Channel* channel);
  void removeAllChannel();
  bool hasChannel(Channel* channel);
  size_t getChannelSetSize();
  void pushRemainRequestBuffer(const std::string& remainRequestBuffer);
  const std::string popRemainRequestBuffer();
  const std::set<const int> getAllChannelClientFd() const;
};

#endif
