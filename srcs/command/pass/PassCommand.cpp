#include "PassCommand.hpp"

PassCommand::PassCommand() : ACommand() {}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(const PassCommand& other) { static_cast<void>(other); }

PassCommand& PassCommand::operator=(const PassCommand& other) {
  static_cast<void>(other);
  return *this;
}

std::string PassCommand::execute(ServerParam& serverParam,
                                 ParsedParam& parsedParam) {
  if (serverParam.getClient(parsedParam.getSenderSocketFd()) != NULL) {
    return this->replyMessage.errAlreadyRegistered(parsedParam);
  }
  if (parsedParam.getPassword().empty() == true) {
    return this->replyMessage.errNeedMoreParams(parsedParam);
  }
  if (parsedParam.getPassword() == serverParam.getServerPassword()) {
    return "";
  }
  return this->replyMessage.errPasswdMismatch(parsedParam);
}
