#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <set>
#include <string>

#include "../channel/Channel.hpp"

class Client {
 private:
  int clientFd;
  std::string nickname;
  std::string username;
  std::set<Channel*> channelSet;
  Client();

 public:
  Client(const int& clientFd);
  ~Client();
  Client(const Client& other);
  Client& operator=(const Client& other);
  const int& getClientFd() const;
  const std::string& getNickname() const;
  const std::string& getUsername() const;
  std::set<Channel*>& getChannelSet();
  void setNickname(const std::string& nickname);
  void setUsername(const std::string& username);
  void addChannel(Channel* channel);
  void removeChannel(Channel* channel);
  void removeAllChannel();
  bool hasChannel(Channel* channel);
  const size_t& getChannelSetSize();
};

#endif
