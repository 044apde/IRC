#include "NickCommand.hpp"

NickCommand::NickCommand() : ACommand() {}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(const NickCommand& other) { static_cast<void>(other); }

NickCommand& NickCommand::operator=(const NickCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool NickCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam,
                                  const std::string& senderNickname) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();
  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNoNicknameGiven(senderNickname));
    return false;
  }
  if (parameter.size() > 1 || isTrailing(parameter[0]) == true) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam NickCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string prevNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, prevNickname) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const std::string newNickname = parameter[0];
  const std::string& senderUsername = senderClient->getUsername();
  const std::string& senderHost = senderClient->getHost();

  if (isValidNickname(newNickname) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errErroneusNickname(prevNickname, newNickname));
    if (prevNickname.empty() == true) {
      commandResponse.addResponseMessage(-2, "");
    }
  } else if (serverParam.getClientByNickname(newNickname) != NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNicknameInUse(prevNickname, newNickname));
    if (prevNickname.empty() == true) {
      commandResponse.addResponseMessage(-2, "");
    }
    // seonghle
    // commandResponse.addResponseMessage(-1, "");
  } else {
    senderClient->setNickname(newNickname);
    commandResponse.addMultipleClientResponseMessage(
        senderClient->getAllChannelClientFd(),
        this->replyMessage.successNick(prevNickname, senderUsername, senderHost,
                                       newNickname));
  }
  return commandResponse;
}
