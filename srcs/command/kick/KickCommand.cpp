#include "KickCommand.hpp"

KickCommand::KickCommand() : ACommand() {}

KickCommand::~KickCommand() {}

KickCommand::KickCommand(const KickCommand &other) { static_cast<void>(other); }

KickCommand &KickCommand::operator=(const KickCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool KickCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 3 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true ||
      (parameter.size() == 3 && isTrailing(parameter[2]) == false)) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

CommandResponseParam KickCommand::execute(ServerParam &serverParam,
                                          const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  int senderSocketFd = tokenParam.getSenderSocketFd();
  Channel *channel = serverParam.getChannel(parameter[0]);
  Client *senderClient = serverParam.getClient(senderSocketFd);
  Client *kickTargetClient = serverParam.getClientByNickname(parameter[1]);

  if (serverParam.getChannel(parameter[0]) == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", parameter[0]));
  } else if (kickTargetClient == NULL ||
             channel->isClientInChannel(kickTargetClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUserNotInChannel("", parameter[1], parameter[0]));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", parameter[0]));
  } else if (channel->isOpClient(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded("", parameter[0]));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(this->replyMessage.successKick(
        parameter[0], parameter[1], parameter[2]));
    serverParam.removeClientAndChannelEachOther(kickTargetClient, channel);
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}