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
    commandResponse.setResponseMessage(
        this->replyMessage.errAlreadyRegistered(parsedParam));
  } else if (parsedParam.getPassword().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (parsedParam.getPassword() == serverParam.getServerPassword()) {
    serverParam.addClient(parsedParam.getSenderSocketFd(), new Client());
    commandResponse.setResponseMessage("");
  } else {
    commandResponse.setResponseMessage(
        this->replyMessage.errPasswdMismatch(parsedParam));
  }
  return commandResponse;
}
