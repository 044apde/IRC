#include "ParsedParam.hpp"

ParsedParam::ParsedParam()
    : senderSocketFd(-1),
      fullMessage(""),
      command(""),
      username(""),
      nickname(""),
      channel(""),
      topic(""),
      modeChar('\0') {}

ParsedParam::ParsedParam(const int& senderSocketFd,
                         const std::string& fullMessage,
                         const std::string& command,
                         const std::string& username,
                         const std::string& nickname,
                         const std::string& channel, const std::string& topic,
                         const char& modeChar)
    : senderSocketFd(senderSocketFd),
      fullMessage(fullMessage),
      command(command),
      username(username),
      nickname(nickname),
      channel(channel),
      topic(topic),
      modeChar(modeChar) {}

ParsedParam::ParsedParam(const ParsedParam& src)
    : senderSocketFd(src.senderSocketFd),
      fullMessage(src.fullMessage),
      command(src.command),
      username(src.username),
      nickname(src.nickname),
      channel(src.channel),
      topic(src.topic),
      modeChar(src.modeChar) {}

ParsedParam& ParsedParam::operator=(const ParsedParam& src) { return *this; }

ParsedParam::~ParsedParam() {}

const int& ParsedParam::getSenderSocketFd() {
  assert(this->senderSocketFd > 2);
  return this->senderSocketFd;
}

const std::string& ParsedParam::getFullMessage() {
  assert(this->fullMessage.empty() == false);
  return this->fullMessage;
}

const std::string& ParsedParam::getCommand() {
  assert(this->command.empty() == false);
  return this->command;
}

const std::string& ParsedParam::getUsername() {
  assert(this->username.empty() == false);
  return this->username;
}

const std::string& ParsedParam::getNickname() {
  assert(this->nickname.empty() == false);
  return this->nickname;
}

const std::string& ParsedParam::getChannel() {
  assert(this->channel.empty() == false);
  return this->channel;
}

const std::string& ParsedParam::getTopic() {
  assert(this->topic.empty() == false);
  return this->topic;
}

const char& ParsedParam::getModeChar() {
  assert(this->modeChar != '\0');
  return this->modeChar;
}
