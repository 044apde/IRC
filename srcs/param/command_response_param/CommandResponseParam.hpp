#pragma once
#ifndef COMMAND_RESPONSE_PARAM_HPP
#define COMMAND_RESPONSE_PARAM_HPP

#include <cassert>
#include <set>
#include <string>

class CommandResponseParam {
 private:
  std::set<int> targetClientFdSet;
  std::string responseMessage;

 public:
  CommandResponseParam();
  ~CommandResponseParam();
  CommandResponseParam(const CommandResponseParam& other);
  CommandResponseParam& operator=(const CommandResponseParam& other);
  void addTargetClientFd(const int& targetClientFd);
  void setResponseMessage(const std::string& responseMessage);
  std::set<int>& getTargetClientFdSet() const;
  const std::string& getResponseMessage() const;
};

#endif
