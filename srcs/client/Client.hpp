#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cassert>
#include <set>
#include <string>

#include "../channel/Channel.hpp"

class Client {
 private:
  int clientFd;
  std::string nickname;
  std::string username;
  std::string remainRequestBuffer;

 public:
  void pushRemainRequestBuffer(const std::string& remainRequestBuffer);
  const std::string popRemainRequestBuffer();
};

#endif