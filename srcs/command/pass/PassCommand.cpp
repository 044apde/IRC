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

  commandResponse.addTargetClientFd(parsedParam.getSenderSocketFd());
  if (serverParam.getClient(parsedParam.getSenderSocketFd()) != NULL) {
    commandResponse.addResponseMessage(
        this->replyMessage.errAlreadyRegistered(parsedParam));
  } else if (parsedParam.getPassword().empty() == true) {
    commandResponse.addResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (parsedParam.getPassword() == serverParam.getServerPassword()) {
    commandResponse.addResponseMessage("");
  } else {
    commandResponse.addResponseMessage(
        this->replyMessage.errPasswdMismatch(parsedParam));
  }
  return commandResponse;
}
