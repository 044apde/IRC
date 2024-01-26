#include "TopicCommand.hpp"

TopicCommand::TopicCommand() : ACommand() {}

TopicCommand::~TopicCommand() {}

TopicCommand::TopicCommand(const TopicCommand& other) {
  static_cast<void>(other);
}

TopicCommand& TopicCommand::operator=(const TopicCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool TopicCommand::isValidParamter(CommandResponseParam& commandResponse,
                                   const TokenParam& tokenParam) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  } else if (parameter.size() > 2 || (isTrailing(parameter[0]) == true ||
                                      isTrailing(parameter[1]) == false)) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

CommandResponseParam TopicCommand::execute(ServerParam& serverParam,
                                           const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  Client* client = serverParam.getClient(tokenParam.getSenderSocketFd());
  Channel* channel = serverParam.getChannel(parameter[0]);
  Channel* topic = serverParam.getChannel(parameter[1]);

  if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", parameter[0]));
  } else if (serverParam.getChannel(parameter[0])->isClientInChannel(client) ==
             false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", parameter[0]));
  } else if (parameter.size() > 1) {
    if (channel->getIsSetTopicOnly() == true &&
        serverParam.getChannel(parameter[0])->isOpClient(client) == false) {
      commandResponse.setResponseMessage(
          this->replyMessage.errChaNoPrivsNeeded("", parameter[0]));
    } else {
      channel->setTopic(parameter[1]);
      channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    }
  } else {
    if (channel->getTopic().empty() == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.rplNoTopic("", parameter[0]));
    } else {
      commandResponse.setResponseMessage(
          this->replyMessage.rplTopic("", parameter[0], parameter[1], ""));
    }
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
  }
  return commandResponse;
}