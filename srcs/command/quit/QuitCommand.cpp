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
  static_cast<void>(commandResponse);
  static_cast<void>(tokenParam);
  return true;
}

CommandResponseParam QuitCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  int senderSocketFd = tokenParam.getSenderSocketFd();
  std::string reason;
  if (parameter.size() == 1) {
    reason = parameter[0];
  }
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  commandResponse.addMultipleClientResponseMessage(
      senderClient->getAllChannelClientFd(),
      this->replyMessage.successQuit(senderNickname, reason));
  commandResponse.addResponseMessage(-1, "");
  commandResponse.removeTarget(senderSocketFd);
  return commandResponse;
}