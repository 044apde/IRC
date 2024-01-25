#include "PingCommand.hpp"

PingCommand::PingCommand() : ACommand() {}

PingCommand::~PingCommand() {}

PingCommand::PingCommand(const PingCommand& other) { static_cast<void>(other); }

PingCommand& PingCommand::operator=(const PingCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam PingCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  // 클라이언트와 서버의 연결이 잘 되었는지
  std::string server = parsedParam.getServerName();
  if (server.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoOrigin(parsedParam));
  }
  // pong 줘야됨
  else {
    commandResponse.setResponseMessage(
        this->replyMessage.successPing(parsedParam));
  }
  // responseMessage를 받을 clientFd 설정
  commandResponse.addTargetClientFd(parsedParam.getSenderSocketFd());

  return commandResponse;
}