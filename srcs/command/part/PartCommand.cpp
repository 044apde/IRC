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
  if (parameter.size() > 2 || isTariling(parameter[0]) == true ||
      isTariling(parameter[1]) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
}

CommandResponseParam PartCommand::execute(ServerParam &serverParam,
                                          TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  int senderSocketFd = tokenParam.getSenderSocketFd();
  Channel *channel = serverParam.getChannel(parameter[0]);
  Client *client = serverParam.getClient(senderSocketFd);

  if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", parameter[0]));
  } else if (client == NULL || channel->isClientInChannel(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", parameter[0]));
  } else {
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    commandResponse.setResponseMessage(
        this->replyMessage.successPart(parameter[0], parameter[1]));
    serverParam.removeClientAndChannelEachOther(client, channel);
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}
