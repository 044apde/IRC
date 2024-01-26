#include "PingCommand.hpp"

PingCommand::PingCommand() : ACommand() {}

PingCommand::~PingCommand() {}

PingCommand::PingCommand(const PingCommand& other) { static_cast<void>(other); }

PingCommand& PingCommand::operator=(const PingCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool PingCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();
  if (parameter.size() < 1) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

CommandResponseParam PingCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string& serverName = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (serverName.empty() == true) {
    commandResponse.setResponseMessage(this->replyMessage.errNoOrigin(""));
  } else {
    commandResponse.setResponseMessage(
        this->replyMessage.successPing(serverName));
  }

  commandResponse.addTargetClientFd(senderSocketFd);

  return commandResponse;
}