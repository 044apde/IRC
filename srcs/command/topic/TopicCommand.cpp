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
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    return false;
  } else if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
             (parameter.size() == 2 && isTrailing(parameter[1]) == false)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
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
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& channelName = parameter[0];
  std::string changedTopic;
  if (parameter.size() == 2) {
    changedTopic = parameter[1];
  }
  Channel* channel = serverParam.getChannel(channelName);

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNoSuchChannel("", channelName));
  } else if (serverParam.getChannel(channelName)
                 ->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotOnChannel("", channelName));
  } else if (parameter.size() > 1) {
    if (channel->isSetTopicOpOnlyChannel() == true &&
        serverParam.getChannel(channelName)->isOpClient(senderClient) ==
            false) {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.errChaNoPrivsNeeded("", channelName));
    } else {
      channel->setTopic(changedTopic);
      commandResponse.addMultipleClientResponseMessage(
          channel->getAllClientFd(),
          this->replyMessage.successTopic(senderClient->getNickname(),
                                          channelName, changedTopic));
    }
  } else {
    if (channel->getTopic().empty() == true) {
      commandResponse.addResponseMessage(
          senderSocketFd, this->replyMessage.rplNoTopic("", channelName));
    } else {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.rplTopic("", channelName, changedTopic,
                                      channel->getTopic()));
    }
  }
  return commandResponse;
}