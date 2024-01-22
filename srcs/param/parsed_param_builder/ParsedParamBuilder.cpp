#include "ParsedParamBuilder.hpp"

ParsedParamBuilder::ParsedParamBuilder()
    : _senderSocketFd(-1),
      _fullMessage(""),
      _command(""),
      _username(""),
      _nickname(""),
      _channel(""),
      _topic(""),
      _modeChar('\0') {}

ParsedParamBuilder::ParsedParamBuilder(const ParsedParamBuilder& src) {
  static_cast<void>(src);
}

ParsedParamBuilder& ParsedParamBuilder::operator=(
    const ParsedParamBuilder& src) {
  static_cast<void>(src);
  return *this;
}

ParsedParamBuilder::~ParsedParamBuilder() {}

ParsedParamBuilder& ParsedParamBuilder::senderSocketFd(
    const int senderSocketFd) {
  assert(senderSocketFd > 2);
  this->_senderSocketFd = senderSocketFd;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::fullMessage(
    const std::string& fullMessage) {
  assert(fullMessage.empty() == false);
  this->_fullMessage = fullMessage;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::command(const std::string& command) {
  assert(command.empty() == false);
  this->_command = command;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::username(const std::string& username) {
  assert(username.empty() == false);
  this->_username = username;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::nickname(const std::string& nickname) {
  assert(nickname.empty() == false);
  this->_nickname = nickname;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::channel(const std::string& channel) {
  assert(channel.empty() == false);
  this->_channel = channel;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::topic(const std::string& topic) {
  assert(topic.empty() == false);
  this->_topic = topic;
  return *this;
}

ParsedParamBuilder& ParsedParamBuilder::modeChar(const char& modeChar) {
  assert(modeChar == 'i' || modeChar == 't' || modeChar == 'k' ||
         modeChar == 'o' || modeChar == 'l');
  this->_modeChar = modeChar;
  return *this;
}

ParsedParam ParsedParamBuilder::build() {
  assert(this->_senderSocketFd != -1 || this->_fullMessage.empty() == false ||
         this->_command.empty() == false || this->_username.empty() == false ||
         this->_nickname.empty() == false || this->_channel.empty() == false ||
         this->_topic.empty() == false || this->_modeChar == 'i' ||
         this->_modeChar == 't' || this->_modeChar == 'k' ||
         this->_modeChar == 'o' || this->_modeChar == 'l');
  return ParsedParam(this->_senderSocketFd, this->_fullMessage, this->_command,
                     this->_username, this->_nickname, this->_channel,
                     this->_topic, this->_modeChar);
}
