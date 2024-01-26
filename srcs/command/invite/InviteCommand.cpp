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
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 3 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
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
  const std::string& nickname = parameter[0];
  const std::string& channelName = parameter[1];
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  Client* inviteTargetClient = serverParam.getClientByNickname(nickname);
  Channel* channel = serverParam.getChannel(channelName);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", channelName));
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isOpClient(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded("", channelName));
  } else if (inviteTargetClient == NULL) {
    // TODO: UB, 대상 사용자가 서버에 아예 없는 경우
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchNick("", nickname));
  } else if (channel->isClientInChannel(inviteTargetClient) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUserOnChannel("", nickname, channelName));
  } else {
    channel->inviteClient(inviteTargetClient);
    commandResponse.setResponseMessage(
        this->replyMessage.rplInviting("", nickname, channelName));
    commandResponse.addTargetClientFd(inviteTargetClient->getClientFd());
  }
  commandResponse.addTargetClientFd(senderSocketFd);
  return commandResponse;
}