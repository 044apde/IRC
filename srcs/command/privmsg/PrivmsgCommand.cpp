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
                                     const TokenParam &tokenParam,
                                     const std::string &senderNickname) {
  const std::vector<std::string> &parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNoRecipient(senderNickname,
                                          tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNoTextToSend(senderNickname));
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PrivmsgCommand::execute(ServerParam &serverParam,
                                             const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;
  const int &senderSocketFd = tokenParam.getSenderSocketFd();
  Client *senderClient = serverParam.getClient(senderSocketFd);
  const std::string &senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  const std::vector<std::string> &parameter = tokenParam.getParameter();
  const std::string &sendTarget = parameter[0];
  const std::string &message = parameter[1];
  Channel *targetChannel = serverParam.getChannel(sendTarget);
  Client *targetClient = serverParam.getClientByNickname(sendTarget);
  bool isChannel = false;

  if (sendTarget[0] == '#') {
    isChannel = true;
  }

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if ((isChannel == true && targetChannel == NULL) ||
             ((isChannel == false &&
               (targetClient == NULL ||
                isRegisteredClient(targetClient) == false)))) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchNick(senderNickname, sendTarget));
  } else if (targetChannel != NULL &&
             targetChannel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errCannotSendToChan(senderNickname, sendTarget));
  } else if (targetClient != NULL) {
    commandResponse.addResponseMessage(
        targetClient->getClientFd(),
        this->replyMessage.successPrivmsg(senderNickname, sendTarget, message));
  } else {
    commandResponse.addMultipleClientResponseMessage(
        targetChannel->getAllClientFd(),
        this->replyMessage.successPrivmsg(senderNickname, sendTarget, message));
    commandResponse.removeTarget(senderSocketFd);
  }
  return commandResponse;
}
