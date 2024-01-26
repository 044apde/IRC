#pragma once
#ifndef SERVER_PARAM_HPP
#define SERVER_PARAM_HPP

#include <cassert>
#include <map>
#include <string>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"

// 미구현 클래스 선언
class Channel;

class ServerParam {
 private:
  int serverFd;
  std::string serverPassword;
  std::map<int, Client*> clientMap;

 public:
  ServerParam();
  ~ServerParam();
  ServerParam(const ServerParam& other);
  ServerParam& operator=(const ServerParam& other);
  void setServerFd(const int& serverFd);
  void setServerPassword(const std::string& serverPassword);
  const int& getServerFd() const;
  const std::string& getServerPassword() const;
  void addNewClient(const int& clientFd);
  void removeClient(const int& clientFd);
  Client* getClient(const int& clientFd) const;
  Client* getClientByNickname(const std::string& nickname) const;
};

#endif