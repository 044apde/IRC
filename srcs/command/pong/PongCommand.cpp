#include "PongCommand.hpp"

PongCommand::PongCommand() : ACommand() {}

PongCommand::~PongCommand() {}

PongCommand::PongCommand(const PongCommand& other) { static_cast<void>(other); }

PongCommand& PongCommand::operator=(const PongCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool PongCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam,
                                  const std::string& senderNickname) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 1 ||
      (parameter.size() == 1 && isTrailing(parameter[0]) == true)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PongCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& token = parameter[0];

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (parameter.size() == 1 && token.empty() == true) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNoOrigin(senderNickname));
  }
  return commandResponse;
}