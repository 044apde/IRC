#include "NickCommand.hpp"

NickCommand::NickCommand() : ACommand() {}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(const NickCommand& other) { static_cast<void>(other); }

NickCommand& NickCommand::operator=(const NickCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool NickCommand::isInvalidNickname(const std::string& nickname) const {
  if (nickname[0] == '#' || nickname[0] == '&' || nickname[0] == ':' ||
      nickname[0] == ' ' || std::isdigit(nickname[0]) == true ||
      nickname.size() > 9) {
    return true;
  }
  return false;
}

bool NickCommand::isSameStrWithLowercase(const std::string& str1,
                                         const std::string& str2) const {
  if (str1.size() != str2.size()) {
    return false;
  }
  for (size_t i = 0; i < str1.size(); ++i) {
    if (std::tolower(str1[i]) != std::tolower(str2[i])) {
      return false;
    }
  }
  return true;
}

CommandResponseParam NickCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  std::string nickname = parsedParam.getNickname();

  if (nickname.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoNicknameGiven(parsedParam));
  } else if (isInvalidNickname(nickname) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errErroneusNickname(parsedParam));
  } else if (serverParam.getClientByNickname(nickname) != NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNicknameInUse(parsedParam));
  }
  if (commandResponse.getResponseMessage().empty() == false) {
    serverParam.removeClient(parsedParam.getSenderSocketFd());
    commandResponse.addTargetClientFd(parsedParam.getSenderSocketFd());
  }
  return commandResponse;
}
