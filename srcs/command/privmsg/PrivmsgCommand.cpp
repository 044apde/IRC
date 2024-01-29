#include "PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand() : ACommand() {}

PrivmsgCommand::~PrivmsgCommand() {}

PrivmsgCommand::PrivmsgCommand(const PrivmsgCommand &other) {
  static_cast<void>(other);
}

PrivmsgCommand &PrivmsgCommand::operator=(const PrivmsgCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool PrivmsgCommand::isValidParamter(CommandResponseParam &commandResponse,
                                     const TokenParam &tokenParam) {
  const std::vector<std::string> &parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNoRecipient("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(tokenParam.getSenderSocketFd(),
                                       this->replyMessage.errNoTextToSend(""));
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PrivmsgCommand::execute(ServerParam &serverParam,
                                             const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  const std::vector<std::string> &parameter = tokenParam.getParameter();
  const int &senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string &sendTarget = parameter[0];
  const std::string &message = parameter[1];
  Client *senderClient = serverParam.getClient(senderSocketFd);
  const std::string &senderClientNickname = senderClient->getNickname();
  Channel *targetChannel = serverParam.getChannel(sendTarget);
  Client *targetClient = serverParam.getClientByNickname(sendTarget);
  bool isChannel = false;

  if (sendTarget[0] == '#') {
    isChannel = true;
  }

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNotRegisterd());
  } else if ((isChannel == true && targetChannel == NULL) ||
             ((isChannel == false &&
               (targetClient == NULL ||
                isRegisteredClient(targetClient) == false)))) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNoSuchNick("", sendTarget));
  } else if (targetChannel != NULL &&
             targetChannel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errCannotSendToChan("", sendTarget));
  } else if (targetClient != NULL) {
    // 개인 메세지
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.successPrivmsg(senderClientNickname,
                                                          sendTarget, message));
    commandResponse.addResponseMessage(
        targetClient->getClientFd(),
        this->replyMessage.successPrivmsg(senderClientNickname, sendTarget,
                                          message));
  } else {
    // 채널 메세지
    commandResponse.addMultipleClientResponseMessage(
        targetChannel->getAllClientFd(),
        this->replyMessage.successPrivmsg(senderClientNickname, sendTarget,
                                          message));
  }
  return commandResponse;
}
