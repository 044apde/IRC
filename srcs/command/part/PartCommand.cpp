#include "PartCommand.hpp"

PartCommand::PartCommand() : ACommand() {}

PartCommand::~PartCommand() {}

PartCommand::PartCommand(const PartCommand &other) { static_cast<void>(other); }

PartCommand &PartCommand::operator=(const PartCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool PartCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam,
                                  const std::string &senderNickname) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      (parameter.size() == 2 && isTrailing(parameter[1]) == false)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam PartCommand::execute(ServerParam &serverParam,
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
  std::string reason;
  if (parameter.size() == 2) {
    reason = parameter[1];
  }
  Channel *channel = serverParam.getChannel(channelName);

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
  } else {
    commandResponse.addMultipleClientResponseMessage(
        channel->getAllClientFd(),
        this->replyMessage.successPart(
            senderNickname, senderClient->getUsername(),
            senderClient->getHost(), channelName, reason));
    serverParam.removeClientAndChannelEachOther(senderClient, channel);
  }
  return commandResponse;
}
