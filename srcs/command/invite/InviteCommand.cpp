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
                                    const TokenParam& tokenParam,
                                    const std::string& senderNickname) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 3 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam InviteCommand::execute(ServerParam& serverParam,
                                            const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const std::string& invitedNickname = parameter[0];
  const std::string& channelName = parameter[1];
  Client* inviteTargetClient = serverParam.getClientByNickname(invitedNickname);
  Channel* channel = serverParam.getChannel(channelName);
  const std::string& senderUsername = senderClient->getUsername();
  const std::string& senderHost = senderClient->getHost();

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchChannel(senderNickname, channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNotOnChannel(senderNickname, channelName));
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isOpClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errChaNoPrivsNeeded(senderNickname, channelName));
  } else if (inviteTargetClient == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchNick(senderNickname, invitedNickname));
  } else if (channel->isClientInChannel(inviteTargetClient) == true) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errUserOnChannel(invitedNickname, channelName));
  } else {
    channel->inviteClient(inviteTargetClient);
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.rplInviting(
                            senderNickname, invitedNickname, channelName));
    commandResponse.addResponseMessage(
        inviteTargetClient->getClientFd(),
        this->replyMessage.successInvite(senderNickname, channelName,
                                         senderHost, senderUsername,
                                         invitedNickname));
  }
  return commandResponse;
}
