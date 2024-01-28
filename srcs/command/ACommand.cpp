#include "ACommand.hpp"

ACommand::ACommand() : replyMessage(ReplyMessage::getInstance()) {}

ACommand::~ACommand() {}

ACommand::ACommand(const ACommand& other)
    : replyMessage(ReplyMessage::getInstance()) {
  static_cast<void>(other);
}

ACommand& ACommand::operator=(const ACommand& other) {
  static_cast<void>(other);
  return *this;
}

bool ACommand::isValidNickname(const std::string& nickname) {
  // TODO: https://modern.ircdocs.horse/#clients
  // 위 규칙에 맞게 유효성 검사
  if (nickname.size() > 9) {
    return false;
  }
  return true;
}
bool ACommand::isValidChannelName(const std::string& channelName) {
  // TODO: https://modern.ircdocs.horse/#channels
  // 위 규칙에 맞게 유효성 검사
}

bool ACommand::isRegisteredClient(Client* client) {
  if (client == NULL || client->getNickname().size() == 0 ||
      client->getUsername().size() == 0) {
    return false;
  }
  return true;
}

bool ACommand::isTrailing(const std::string& str) {
  if (str.size() != 0 && str[0] == ':') {
    return true;
  }
  return false;
}
