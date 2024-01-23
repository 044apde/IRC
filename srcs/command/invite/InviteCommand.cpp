#include "InviteCommand.hpp"

InviteCommand::InviteCommand() : ACommand() {}

InviteCommand::~InviteCommand() {}

InviteCommand::InviteCommand(const InviteCommand& other) {
  static_cast<void>(other);
}

InviteCommand& InviteCommand::operator=(const InviteCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam InviteCommand::execute(ServerParam& serverParam,
                                            ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  Client* client = serverParam.getClient(parsedParam.getSenderSocketFd());
  assert(client != NULL);
  Channel* channel = serverParam.getChannel(parsedParam.getChannel());

  if (parsedParam.getNickname().empty() == true ||
      parsedParam.getChannel().empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (client == NULL || channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchNick(parsedParam));
  } else if (channel->isClientInChannel(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel(parsedParam));
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isOpClient(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded(parsedParam));
  } else if (channel->isClientInChannelByNickname(parsedParam.getNickname()) ==
             true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUserOnChannel(parsedParam));
  } else {
    channel->inviteClient(
        serverParam.getClientByNickname(parsedParam.getNickname()));
    commandResponse.setResponseMessage(
        this->replyMessage.rplInviting(parsedParam));
  }
  return commandResponse;
}