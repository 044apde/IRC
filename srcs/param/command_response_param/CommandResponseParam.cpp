#include "CommandResponseParam.hpp"

CommandResponseParam::CommandResponseParam() {}

CommandResponseParam::~CommandResponseParam() {}

CommandResponseParam::CommandResponseParam(const CommandResponseParam& other) {
  *this = other;
}

CommandResponseParam& CommandResponseParam::operator=(
    const CommandResponseParam& other) {
  if (this != &other) {
    this->clientResponseMessageMap = other.clientResponseMessageMap;
  }
  return *this;
}

void CommandResponseParam::addResponseMessage(
    const int& targetClientFd, const std::string& responseMessage) {
  this->clientResponseMessageMap.insert(
      std::make_pair(targetClientFd, responseMessage));
  return;
}

void CommandResponseParam::addMultipleClientResponseMessage(
    const std::set<const int>& targetClientFdSet,
    const std::string& responseMessage) {
  for (std::set<const int>::iterator it = targetClientFdSet.begin();
       it != targetClientFdSet.end(); it++) {
    addResponseMessage(*it, responseMessage);
  }
  return;
}

const std::map<const int, const std::string>&
CommandResponseParam::getClientResponseMessageMap() const {
  return this->clientResponseMessageMap;
}

void CommandResponseParam::removeTarget(const int targetClientFd) {
  this->clientResponseMessageMap.erase(targetClientFd);
  return;
}
