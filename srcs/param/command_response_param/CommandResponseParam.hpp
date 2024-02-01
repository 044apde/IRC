#pragma once
#ifndef COMMAND_RESPONSE_PARAM_HPP
#define COMMAND_RESPONSE_PARAM_HPP

#include <map>
#include <set>
#include <string>

class CommandResponseParam {
 private:
  std::map<const int, const std::string> clientResponseMessageMap;

 public:
  CommandResponseParam();
  ~CommandResponseParam();
  CommandResponseParam(const CommandResponseParam& other);
  CommandResponseParam& operator=(const CommandResponseParam& other);
  void addResponseMessage(const int& targetClientFd,
                          const std::string& responseMessage);
  void addMultipleClientResponseMessage(
      const std::set<const int>& targetClientFdSet,
      const std::string& responseMessage);
  const std::map<const int, const std::string>& getClientResponseMessageMap()
      const;
  void addTerminateClientAfterSendResponseMessage();
  void addTerminateClientImmediateResponseMessage();
  void removeTarget(const int targetClientFd);
};

#endif
