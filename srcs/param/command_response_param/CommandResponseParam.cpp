#include "CommandResponseParam.hpp"

CommandResponseParam::CommandResponseParam() {}

CommandResponseParam::~CommandResponseParam() {}

CommandResponseParam::CommandResponseParam(const CommandResponseParam& other) {
  *this = other;
}

CommandResponseParam& CommandResponseParam::operator=(
    const CommandResponseParam& other) {
  if (this != &other) {
    this->targetClientFdSet = other.targetClientFdSet;
    this->responseMessage = other.responseMessage;
  }
  return *this;
}

void CommandResponseParam::addTargetClientFd(const int& targetClientFd) {
  assert(targetClientFd > 2);
  assert(this->targetClientFdSet.find(targetClientFd) ==
         this->targetClientFdSet.end());
  this->targetClientFdSet.insert(targetClientFd);
  return;
}

void CommandResponseParam::setResponseMessage(
    const std::string& responseMessage) {
  this->responseMessage = responseMessage;
  return;
}

std::set<int> CommandResponseParam::getTargetClientFdSet() const {
  assert(this->targetClientFdSet.empty() == false);
  return this->targetClientFdSet;
}

std::string CommandResponseParam::getResponseMessage() const {
  assert(this->responseMessage.empty() == false);
  return this->responseMessage;
}
