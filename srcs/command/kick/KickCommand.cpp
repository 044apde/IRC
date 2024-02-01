#include "KickCommand.hpp"

KickCommand::KickCommand() : ACommand() {}

KickCommand::~KickCommand() {}

KickCommand::KickCommand(const KickCommand &other) { static_cast<void>(other); }

KickCommand &KickCommand::operator=(const KickCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool KickCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam,
                                  const std::string &senderNickname) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 3 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true ||
      (parameter.size() == 3 && isTrailing(parameter[2]) == false)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam KickCommand::execute(ServerParam &serverParam,
                                          const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  int senderSocketFd = tokenParam.getSenderSocketFd();
  Client *senderClient = serverParam.getClient(senderSocketFd);
  const std::string &senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string &channelName = parameter[0];
  const std::string &targetNickname = parameter[1];
  std::string commnet;
  if (parameter.size() == 3) {
    commnet = parameter[2];
  }
  Channel *channel = serverParam.getChannel(channelName);
  Client *kickTargetClient = serverParam.getClientByNickname(targetNickname);
  const std::string &senderHost = senderClient->getHost();
  const std::string &senderUsername = senderClient->getUsername();

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchChannel(senderNickname, channelName));
  } else if (kickTargetClient == NULL ||
             channel->isClientInChannel(kickTargetClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errUserNotInChannel(
                            senderNickname, targetNickname, channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNotOnChannel(senderNickname, channelName));
  } else if (channel->isOpClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errChaNoPrivsNeeded(senderNickname, channelName));
  } else {
    commandResponse.addMultipleClientResponseMessage(
        channel->getAllClientFd(),
        this->replyMessage.successKick(senderNickname, senderUsername,
                                       senderHost, channelName, targetNickname,
                                       commnet));
    serverParam.removeClientAndChannelEachOther(kickTargetClient, channel);
  }
  return commandResponse;
}