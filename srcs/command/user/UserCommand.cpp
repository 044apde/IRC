#include "UserCommand.hpp"

UserCommand::UserCommand() : ACommand() {}

UserCommand::~UserCommand() {}

UserCommand::UserCommand(const UserCommand& other) { static_cast<void>(other); }

UserCommand& UserCommand::operator=(const UserCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool UserCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  const std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 4) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return true;
  }
  if (parameter.size() > 4 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true || isTrailing(parameter[2]) == true ||
      isTrailing(parameter[3]) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return true;
  }
  return true;
}

CommandResponseParam UserCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = tokenParam.getSenderSocketFd();

  if (isValidParamter(commandResponse, tokenParam) == true) {
    serverParam.removeClient(senderSocketFd);
    return commandResponse;
  }

  const std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& username = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);
  bool isSuccess = false;

  if (senderClient == NULL || senderClient->getNickname().empty() == true) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (senderClient->getUsername().empty() == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(""));
  } else {
    senderClient->setUsername(username);
    commandResponse.setResponseMessage(
        this->replyMessage.rplWelcome(
            "", serverParam.getClient(senderSocketFd)->getNickname()) +
        this->replyMessage.rplYourHost("") + this->replyMessage.rplCreated("") +
        this->replyMessage.rplMyInfo(""));
  }
  if (isSuccess == false) {
    serverParam.removeClient(senderSocketFd);
  }
  commandResponse.addTargetClientFd(senderSocketFd);
  return commandResponse;
}