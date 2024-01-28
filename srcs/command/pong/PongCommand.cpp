#include "PongCommand.hpp"

PongCommand::PongCommand() : ACommand() {}

PongCommand::~PongCommand() {}

PongCommand::PongCommand(const PongCommand& other) { static_cast<void>(other); }

PongCommand& PongCommand::operator=(const PongCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool PongCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 1 || isTrailing(parameter[0]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PongCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string& token = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNotRegisterd());
  } else if (parameter.size() == 2 && token.empty() == true) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNoOrigin(""));
  }
  return commandResponse;
}