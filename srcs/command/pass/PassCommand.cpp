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
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 1 || isTrailing(parameter[0]) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

CommandResponseParam PassCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string& password = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);

  if (senderClient->getIsCheckPass() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(""));
  } else if (password != serverParam.getServerPassword()) {
    commandResponse.setResponseMessage(
        this->replyMessage.errPasswdMismatch(""));
  } else {
    senderClient->setIsCheckPassTrue();
  }
  if (commandResponse.getResponseMessage().empty() == false) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
