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

bool ACommand::isChannelNameHasOnlyDigitOrAlpha(
    const std::string& channelName) {
  for (size_t i = 1; i < channelName.size(); i++) {
    if (std::isalnum(channelName[i]) == false &&
        (channelName[i] != '-' && channelName[i] != '_' &&
         channelName[i] != '.')) {
      return false;
    }
  }
  return true;
}

bool ACommand::isValidNickname(const std::string& nickname) {
  if (nickname.size() == 0 || nickname.size() > 9 ||
      std::isalpha(nickname[0]) == false) {
    return false;
  }
  return true;
}

bool ACommand::isValidChannelName(const std::string& channelName) {
  const size_t channelNameSize = channelName.size();
  if (channelNameSize == 0 || channelNameSize > 200 || channelName[0] != '#' ||
      isChannelNameHasOnlyDigitOrAlpha(channelName) == false) {
    return false;
  }
  return true;
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
