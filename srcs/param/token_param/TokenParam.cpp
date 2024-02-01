#include "TokenParam.hpp"

TokenParam::TokenParam()
    : senderSocketFd(-1),
      prefix(""),
      command(""),
      parameter(std::vector<std::string>()) {}

TokenParam::~TokenParam() {}

TokenParam::TokenParam(const int& senderSocketFd, const std::string& prefix,
                       const std::string& command,
                       const std::vector<std::string>& parameter)
    : senderSocketFd(senderSocketFd),
      prefix(prefix),
      command(command),
      parameter(parameter) {}

TokenParam::TokenParam(const TokenParam& other)
    : senderSocketFd(other.senderSocketFd),
      prefix(other.prefix),
      command(other.command),
      parameter(other.parameter) {}

TokenParam& TokenParam::operator=(const TokenParam& other) {
  static_cast<void>(other);
  return *this;
}

const int& TokenParam::getSenderSocketFd() const {
  return this->senderSocketFd;
}

const std::string& TokenParam::getCommand() const { return this->command; }

const std::vector<std::string>& TokenParam::getParameter() const {
  return this->parameter;
}
