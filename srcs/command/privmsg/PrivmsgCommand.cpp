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
    commandResponse.setResponseMessage(
        this->replyMessage.errNoRecipient("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return true;
  }
  if (parameter.size() < 2) {
    commandResponse.setResponseMessage(this->replyMessage.errNoTextToSend(""));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return true;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return true;
  }
  return false;
}

CommandResponseParam PrivmsgCommand::execute(ServerParam &serverParam,
                                             const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == true) {
    return commandResponse;
  }

  const std::vector<std::string> &parameter = tokenParam.getParameter();
  const int &senderSocketFd = tokenParam.getSenderSocketFd();
  bool isChannel = false;
  if (parameter[0].size() > 0 && parameter[0][0] == '#') {
    isChannel = true;
  }
  const std::string &name = parameter[0];
  const std::string &message = parameter[1];
  Channel *channel = serverParam.getChannel(name);
  Client *senderClient = serverParam.getClient(senderSocketFd);
  Client *targetClient = serverParam.getClientByNickname(name);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL || targetClient == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchNick("", name));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errCannotSendToChan("", name));
  } else if (targetClient != NULL) {
    // 개인 메세지
    commandResponse.addTargetClientFd(targetClient->getClientFd());
    commandResponse.setResponseMessage(
        this->replyMessage.successPrivmsg(name, parameter[1]));
  } else {
    // 채널 메세지
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successPrivmsg(name, parameter[1]));
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
