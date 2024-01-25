#include "PassCommand.hpp"

PassCommand::PassCommand() : ACommand() {}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(const PassCommand& other) { static_cast<void>(other); }

PassCommand& PassCommand::operator=(const PassCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam PassCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = parsedParam.getSenderSocketFd();

  if (serverParam.getClient(senderSocketFd) != NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(parsedParam));
  } else if (parsedParam.getServerPassword().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else {
    if (parsedParam.getServerPassword() != serverParam.getServerPassword()) {
      commandResponse.setResponseMessage(
          this->replyMessage.errPasswdMismatch(parsedParam));
    } else {
      serverParam.addNewClient(senderSocketFd);
    }
  }
  if (commandResponse.getResponseMessage().empty() == false) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
