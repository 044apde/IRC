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
  if (parameter.size() > 1 || isTariling(parameter[0]) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

CommandResponseParam PingCommand::execute(ServerParam& serverParam,
                                          TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();

  if (parameter[0].empty() == true) {
    commandResponse.setResponseMessage(this->replyMessage.errNoOrigin(""));
  } else {
    commandResponse.setResponseMessage(
        this->replyMessage.successPing(parameter[0]));
  }

  commandResponse.addTargetClientFd(senderSocketFd);

  return commandResponse;
}