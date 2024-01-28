#include "NickCommand.hpp"

NickCommand::NickCommand() : ACommand() {}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(const NickCommand& other) { static_cast<void>(other); }

NickCommand& NickCommand::operator=(const NickCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool NickCommand::isValidNickname(const std::string& nickname) const {
  if (nickname.empty() == true || nickname[0] == '#' || nickname[0] == '&' ||
      nickname[0] == ':' || nickname[0] == ' ' ||
      std::isdigit(nickname[0]) == true || nickname.size() > 9) {
    return false;
  }
  return true;
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

bool NickCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();
  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNoNicknameGiven(""));
    return false;
  }
  if (parameter.size() > 1 || isTrailing(parameter[0]) == true) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam NickCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string prevNickname = senderClient->getNickname();
  const std::string newNickname = parameter[0];

  if (isValidNickname(newNickname) == true) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errErroneusNickname("", newNickname));
  } else if (serverParam.getClientByNickname(newNickname) != NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNicknameInUse("", newNickname));
  } else {
    senderClient->setNickname(newNickname);
    commandResponse.addMultipleClientResponseMessage(
        senderClient->getAllChannelClientFd(),
        this->replyMessage.successNick(prevNickname, newNickname));
  }
  return commandResponse;
}
