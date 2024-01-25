#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : ACommand() {}

QuitCommand::~QuitCommand() {}

QuitCommand::QuitCommand(const QuitCommand& other) { static_cast<void>(other); }

QuitCommand& QuitCommand::operator=(const QuitCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam QuitCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;

  std::string reason = parsedParam.getNickname();

  if (reason.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.successQuit(parsedParam));
  }
  // 서버에 있는 클라리언트 정보 삭제
  serverParam.removeClient(parsedParam.getSenderSocketFd());
  return commandResponse;
}