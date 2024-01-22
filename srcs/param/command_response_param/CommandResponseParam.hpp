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
  CommandResponseParam(const CommandResponseParam&);
  CommandResponseParam& operator=(const CommandResponseParam&);
  void addTargetClientFd(const int& targetClientFd);
  void addResponseMessage(const std::string& responseMessage);
  std::set<int> getTargetClientFdSet() const;
  std::string getResponseMessage() const;
};

#endif
