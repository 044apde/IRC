#include "PartCommand.hpp"

PartCommand::PartCommand() : ACommand() {}

PartCommand::~PartCommand() {}

PartCommand::PartCommand(const PartCommand &other) { static_cast<void>(other); }

PartCommand &PartCommand::operator=(const PartCommand &other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam PartCommand::execute(ServerParam &serverParam,
                                          ParsedParam &parsedParam) {
  CommandResponseParam commandResponse;
  int senderSocketFd = parsedParam.getSenderSocketFd();
  std::string channelName = parsedParam.getChannelName();
  Channel *channel = serverParam.getChannel(channelName);
  Client *client = serverParam.getClient(senderSocketFd);

  if (parsedParam.getChannelName().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel(parsedParam));
  } else if (client == NULL || channel->isClientInChannel(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel(parsedParam));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successPart(parsedParam));
    serverParam.removeClientAndChannelEachOther(client, channel);
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
