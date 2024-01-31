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

bool InviteCommand::isValidParamter(CommandResponseParam& commandResponse,
                                    const TokenParam& tokenParam) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 3 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam InviteCommand::execute(ServerParam& serverParam,
                                            const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const std::string& invitedNickname = parameter[0];
  const std::string& channelName = parameter[1];
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  Client* inviteTargetClient = serverParam.getClientByNickname(invitedNickname);
  Channel* channel = serverParam.getChannel(channelName);
  const std::string& senderNickname = senderClient->getNickname();
  const std::string& senderUsername = senderClient->getUsername();
  const std::string& senderHost = senderClient->getHost();

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNoSuchChannel("", channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotOnChannel("", channelName));
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isOpClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errChaNoPrivsNeeded("", channelName));
  } else if (inviteTargetClient == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNoSuchNick("", invitedNickname));
  } else if (channel->isClientInChannel(inviteTargetClient) == true) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errUserOnChannel(invitedNickname, channelName));
  } else {
    channel->inviteClient(inviteTargetClient);
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.rplInviting(invitedNickname, channelName));
    commandResponse.addResponseMessage(
        inviteTargetClient->getClientFd(),
        this->replyMessage.successInvite(senderNickname,
                                         channelName, senderHost,
                                         senderUsername, invitedNickname));
  }
  return commandResponse;
}
