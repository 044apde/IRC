#include "ParsedParam.hpp"

ParsedParam::ParsedParam()
    : senderSocketFd(-1),
      command(""),
      serverPassword(""),
      channelKey(""),
      username(""),
      nickname(""),
      channelName(""),
      trailing(""),
      serverName(""),
      modeString("") {}

ParsedParam::ParsedParam(
    const int& senderSocketFd, const std::string& command,
    const std::string& serverPassword, const std::string& channelKey,
    const std::string& username, const std::string& nickname,
    const std::string& channelName, const std::string& trailing,
    const std::string& serverName, const std::string& modeString)
    : senderSocketFd(senderSocketFd),
      command(command),
      username(username),
      serverPassword(serverPassword),
      channelKey(channelKey),
      nickname(nickname),
      channelName(channelName),
      trailing(trailing),
      serverName(serverName),
      modeString(modeString) {}

ParsedParam::ParsedParam(const ParsedParam& other)
    : senderSocketFd(other.senderSocketFd),
      command(other.command),
      serverPassword(other.serverPassword),
      channelKey(other.channelKey),
      username(other.username),
      nickname(other.nickname),
      channelName(other.channelName),
      trailing(other.trailing),
      serverName(other.serverName),
      modeString(other.modeString) {}

ParsedParam& ParsedParam::operator=(const ParsedParam& other) {
  static_cast<void>(other);
  return *this;
}

ParsedParam::~ParsedParam() {}

const int& ParsedParam::getSenderSocketFd() { return this->senderSocketFd; }

const std::string& ParsedParam::getCommand() { return this->command; }

const std::string& ParsedParam::getServerPassword() {
  return this->serverPassword;
}

const std::string& ParsedParam::getChannelKey() { return this->channelKey; }

const std::string& ParsedParam::getUsername() { return this->username; }

const std::string& ParsedParam::getNickname() { return this->nickname; }

const std::string& ParsedParam::getChannelName() { return this->channelName; }

const std::string& ParsedParam::getTrailing() { return this->trailing; }

const std::string& ParsedParam::getServerName() { return this->serverName; }

const std::string& ParsedParam::getModeString() { return this->modeString; }
