#include "PassCommand.hpp"

PassCommand::PassCommand() : ACommand() {}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(const PassCommand& other) { static_cast<void>(other); }

PassCommand& PassCommand::operator=(const PassCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool PassCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam,
                                  const std::string& senderNickname) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 1 ||
      (parameter.size() == 1 && isTrailing(parameter[0]) == true)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PassCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& password = parameter[0];

  if (senderClient->getIsCheckPass() == true) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errAlreadyRegistered(senderNickname));
    // seonghle
    // commandResponse.addResponseMessage(-1, "");
  } else if (password != serverParam.getServerPassword()) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errPasswdMismatch(senderNickname));
    commandResponse.addResponseMessage(-2, "");
  } else {
    senderClient->setIsCheckPassTrue();
  }
  return commandResponse;
}
