#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : ACommand() {}

QuitCommand::~QuitCommand() {}

QuitCommand::QuitCommand(const QuitCommand& other) { static_cast<void>(other); }

QuitCommand& QuitCommand::operator=(const QuitCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool QuitCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() == 1 && parameter[0] != ":") {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 1 && isTariling(parameter[0]) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam QuitCommand::execute(ServerParam& serverParam,
                                          TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1 || parameter.size() == 1 &&
                                  parameter[0].empty() == false &&
                                  parameter[0][0] == 0) {
    commandResponse.setResponseMessage(
        this->replyMessage.successQuit(parameter[0]));
  }
  // 서버에 있는 클라리언트 정보 삭제
  serverParam.removeClient(tokenParam.getSenderSocketFd());

  return commandResponse;
}