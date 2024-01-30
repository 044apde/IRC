#include "PassCommand.hpp"

PassCommand::PassCommand() : ACommand() {}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(const PassCommand& other) { static_cast<void>(other); }

PassCommand& PassCommand::operator=(const PassCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool PassCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 1 ||
      (parameter.size() == 1 && isTrailing(parameter[0]) == true)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PassCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();

  if (isValidParamter(commandResponse, tokenParam) == false) {
    commandResponse.addResponseMessage(-1, "");
    serverParam.removeClient(senderSocketFd);
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& password = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);

  if (senderClient->getIsCheckPass() == true) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errAlreadyRegistered(""));
    commandResponse.addResponseMessage(-1, "");
    serverParam.removeClient(senderSocketFd);
  } else if (password != serverParam.getServerPassword()) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errPasswdMismatch(""));
    commandResponse.addResponseMessage(-1, "");
    serverParam.removeClient(senderSocketFd);
  } else {
    senderClient->setIsCheckPassTrue();
  }
  return commandResponse;
}
