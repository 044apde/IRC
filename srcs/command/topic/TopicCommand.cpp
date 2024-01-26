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
  Client* senderClient = serverParam.getClient(tokenParam.getSenderSocketFd());
  const std::string& channelName = parameter[0];
  const std::string& changedTopic = parameter[1];
  Channel* channel = serverParam.getChannel(channelName);
  Channel* topic = serverParam.getChannel(changedTopic);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", channelName));
  } else if (serverParam.getChannel(channelName)
                 ->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", channelName));
  } else if (parameter.size() > 1) {
    if (channel->getIsSetTopicOnly() == true &&
        serverParam.getChannel(channelName)->isOpClient(senderClient) ==
            false) {
      commandResponse.setResponseMessage(
          this->replyMessage.errChaNoPrivsNeeded("", channelName));
    } else {
      channel->setTopic(parameter[1]);
      channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    }
  } else {
    if (channel->getTopic().empty() == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.rplNoTopic("", channelName));
    } else {
      commandResponse.setResponseMessage(this->replyMessage.rplTopic(
          "", channelName, changedTopic, channel->getTopic()));
    }
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
  }
  return commandResponse;
}