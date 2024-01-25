#include "UserCommand.hpp"

UserCommand::UserCommand() : ACommand() {}

UserCommand::~UserCommand() {}

UserCommand::UserCommand(const UserCommand& other) { static_cast<void>(other); }

UserCommand& UserCommand::operator=(const UserCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam UserCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = parsedParam.getSenderSocketFd();
  Client* client = serverParam.getClient(senderSocketFd);
  bool isSuccess = false;

  commandResponse.addTargetClientFd(senderSocketFd);
  if (parsedParam.getUsername().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (client->getUsername().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(parsedParam));
  } else {
    client->setUsername(parsedParam.getUsername());
    commandResponse.setResponseMessage(
        this->replyMessage.rplWelcome(parsedParam) +
        this->replyMessage.rplYourHost(parsedParam) +
        this->replyMessage.rplCreated(parsedParam) +
        this->replyMessage.rplMyInfo(parsedParam));
    isSuccess = true;
  }
  if (isSuccess == false) {
    serverParam.removeClient(senderSocketFd);
  }
  return commandResponse;
}