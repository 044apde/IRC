#include "ParsedParamBuilder.hpp"

ParsedParamBuilder::ParsedParamBuilder()
    : _senderSocketFd(-1),
      _command(""),
      _serverPassword(""),
      _channelKey(""),
      _username(""),
      _nickname(""),
      _channelName(""),
      _trailing(""),
      _serverName(""),
      _modeString("") {}

ParsedParamBuilder::ParsedParamBuilder(const ParsedParamBuilder& other) {
  static_cast<void>(other);
}

ParsedParamBuilder& ParsedParamBuilder::operator=(
    const ParsedParamBuilder& other) {
  static_cast<void>(other);
  return *this;
}

ParsedParamBuilder::~ParsedParamBuilder() {}

ParsedParamBuilder& ParsedParamBuilder::senderSocketFd(
    const int senderSocketFd) {
  this->_senderSocketFd = senderSocketFd;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::command(const std::string& _command) {
  this->_command = _command;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::serverPassword(
    const std::string& _serverPassword) {
  this->_serverPassword = _serverPassword;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::channelKey(
    const std::string& _channelKey) {
  this->_channelKey = _channelKey;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::username(const std::string& _username) {
  this->_username = _username;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::nickname(const std::string& _nickname) {
  this->_nickname = _nickname;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::channelName(
    const std::string& _channelName) {
  this->_channelName = _channelName;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::trailing(const std::string& _trailing) {
  this->_trailing = _trailing;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::serverName(
    const std::string& _serverName) {
  this->_serverName = _serverName;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::modeString(
    const std::string& _modeString) {
  this->_modeString = _modeString;
  return *this;
}

ParsedParam ParsedParamBuilder::build() {
  return ParsedParam(this->_senderSocketFd, this->_command,
                     this->_serverPassword, this->_channelKey, this->_username,
                     this->_nickname, this->_channelName, this->_trailing,
                     this->_serverName, this->_modeString);
}
