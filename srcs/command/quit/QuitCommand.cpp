#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : ACommand() {}

QuitCommand::~QuitCommand() {}

QuitCommand::QuitCommand(const QuitCommand& other) { static_cast<void>(other); }

QuitCommand& QuitCommand::operator=(const QuitCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool QuitCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam,
                                  const std::string& senderNickname) {
  static_cast<void>(commandResponse);
  static_cast<void>(tokenParam);
  static_cast<void>(senderNickname);
  return true;
}

CommandResponseParam QuitCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  std::string reason;
  if (parameter.size() == 1) {
    reason = parameter[0];
  }
  const std::string& username = senderClient->getUsername();
  const std::string& host = senderClient->getHost();

  commandResponse.addMultipleClientResponseMessage(
      senderClient->getAllChannelClientFd(),
      this->replyMessage.successQuit(senderNickname, username, host, reason));
  commandResponse.addResponseMessage(-1, "");
  commandResponse.removeTarget(senderSocketFd);
  return commandResponse;
}