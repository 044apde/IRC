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

CommandResponseParam PrivmsgCommand::execute(ServerParam &serverParam,
                                             ParsedParam &parsedParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = parsedParam.getSenderSocketFd();
  std::string channelName = parsedParam.getChannel();
  std::string nickname = parsedParam.getNickname();
  Channel *channel = serverParam.getChannel(channelName);
  Client *client = serverParam.getClient(senderSocketFd);
  Client *targetClient = serverParam.getClientByNickname(nickname);

  if (channelName.empty() == true || nickname.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoRecipient(parsedParam));
  } else if (channel == NULL || targetClient == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchNick(parsedParam));
  } else if (channel->isClientInChannel(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errCannotSendToChan(parsedParam));
  } else if (targetClient != NULL) {
    commandResponse.addTargetClientFd(targetClient->getClientFd());
    commandResponse.setResponseMessage(
        this->replyMessage.successPrivmsg(parsedParam));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successPrivmsg(parsedParam));
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
