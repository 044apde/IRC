#include "Client.hpp"

void Client::pushRemainRequestBuffer(const std::string& remainRequestBuffer) {
  this->remainRequestBuffer = remainRequestBuffer;
  return;
}

const std::string Client::popRemainRequestBuffer() {
  std::string tempRemainRequestBuffer = this->remainRequestBuffer;

  this->remainRequestBuffer.clear();
  return tempRemainRequestBuffer;
}