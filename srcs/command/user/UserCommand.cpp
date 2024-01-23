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
  Client* client = serverParam.getClient(parsedParam.getSenderSocketFd());

  if (parsedParam.getUsername().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (client->getUsername().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(parsedParam));
  } else {
    client->setUsername(parsedParam.getUsername());
  }
  return commandResponse;
}