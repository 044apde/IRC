#include "TokenParam.hpp"

TokenParam::TokenParam()
    : prefix(""), command(""), parameter(std::vector<std::string>()) {}

TokenParam::TokenParam(const std::string& prefix, const std::string& command,
                       const std::vector<std::string>& parameter)
    : prefix(prefix), command(command), parameter(parameter) {}

TokenParam::TokenParam(const TokenParam& other)
    : prefix(other.prefix),
      command(other.command),
      parameter(other.parameter) {}

TokenParam& TokenParam::operator=(const TokenParam& other) {
  static_cast<void>(other);
  return *this;
}

TokenParam::~TokenParam() {}

const std::string& TokenParam::getPrefix() const { return this->prefix; }

const std::string& TokenParam::getCommand() const { return this->command; }

const std::vector<std::string>& TokenParam::getParameter() const {
  return this->parameter;
}
