#include "CommandResponseParam.hpp"

CommandResponseParam::CommandResponseParam() {}

CommandResponseParam::~CommandResponseParam() {}

CommandResponseParam::CommandResponseParam(const CommandResponseParam& src) {
  *this = src;
}

CommandResponseParam& CommandResponseParam::operator=(
    const CommandResponseParam& src) {
  if (this != &src) {
    this->targetClientFdSet = src.targetClientFdSet;
    this->responseMessage = src.responseMessage;
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

void CommandResponseParam::addResponseMessage(
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
