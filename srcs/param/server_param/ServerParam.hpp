#pragma once
#ifndef SERVER_PARAM_HPP
#define SERVER_PARAM_HPP

#include <cassert>
#include <map>
#include <string>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"

// 미구현 클래스 선언
class Client;
class Channel;

class ServerParam {
 private:
  int serverFd;
  std::string serverPassword;
  std::map<int, Client*> clientMap;
  std::map<std::string, Channel*> channelMap;

 public:
  ServerParam();
  ~ServerParam();
  ServerParam(const ServerParam& other);
  ServerParam& operator=(const ServerParam& other);
  void setServerFd(const int& serverFd);
  void setServerPassword(const std::string& serverPassword);
  const int& getServerFd() const;
  const std::string& getServerPassword() const;
  bool addClient(const int& clientFd, Client* client);
  bool addChannel(const std::string& channelName, Channel* channel);
  bool removeClient(const int& clientFd);
  bool removeChannel(const std::string& channelName);
  Client* getClient(const int& clientFd) const;
  Channel* getChannel(const std::string& channelName) const;
};

#endif
