#include "PartCommand.hpp"

PartCommand::PartCommand() : ACommand() {}

PartCommand::~PartCommand() {}

PartCommand::PartCommand(const PartCommand &other) { static_cast<void>(other); }

PartCommand &PartCommand::operator=(const PartCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool PartCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      (parameter.size() == 2 && isTrailing(parameter[1]) == false)) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
}

CommandResponseParam PartCommand::execute(ServerParam &serverParam,
                                          const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  int senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string &channelName = parameter[0];
  std::string reason;
  if (parameter.size() == 2) {
    reason = parameter[1];
  }
  Channel *channel = serverParam.getChannel(channelName);
  Client *senderClient = serverParam.getClient(senderSocketFd);
  const std::string &senderNickname = senderClient->getNickname();

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", channelName));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successPart(senderNickname, channelName, reason));
    serverParam.removeClientAndChannelEachOther(senderClient, channel);
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
