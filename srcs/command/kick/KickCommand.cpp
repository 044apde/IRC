#include "KickCommand.hpp"

KickCommand::KickCommand() : ACommand() {}

KickCommand::~KickCommand() {}

KickCommand::KickCommand(const KickCommand &other) { static_cast<void>(other); }

KickCommand &KickCommand::operator=(const KickCommand &other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam KickCommand::execute(ServerParam &serverParam,
                                          ParsedParam &parsedParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = parsedParam.getSenderSocketFd();
  std::string channelName = parsedParam.getChannelName();
  Channel *channel = serverParam.getChannel(channelName);
  Client *senderClient = serverParam.getClient(senderSocketFd);
  Client *kickTargetClient =
      serverParam.getClientByNickname(parsedParam.getNickname());

  if (channelName.empty() == true ||
      parsedParam.getNickname().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (serverParam.getChannel(channelName) == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel(parsedParam));
  } else if (kickTargetClient == NULL ||
             channel->isClientInChannel(kickTargetClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUserNotInChannel(parsedParam));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel(parsedParam));
  } else if (channel->isOpClient(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded(parsedParam));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successKick(parsedParam));
    serverParam.removeClientAndChannelEachOther(kickTargetClient, channel);
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}