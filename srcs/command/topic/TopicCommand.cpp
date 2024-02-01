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
                                   const TokenParam& tokenParam,
                                   const std::string& senderNickname) {
  std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  } else if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
             (parameter.size() == 2 && isTrailing(parameter[1]) == false)) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam TopicCommand::execute(ServerParam& serverParam,
                                           const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* senderClient = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& channelName = parameter[0];
  std::string changedTopic;
  if (parameter.size() == 2) {
    changedTopic = parameter[1];

    size_t newLineCharIndex = changedTopic.find('\n');
    if (newLineCharIndex != std::string::npos) {
      changedTopic = changedTopic.substr(0, newLineCharIndex);
    }
  }
  Channel* channel = serverParam.getChannel(channelName);
  const std::string& username = senderClient->getUsername();
  const std::string& host = senderClient->getHost();

  if (isRegisteredClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchChannel(senderNickname, channelName));
  } else if (serverParam.getChannel(channelName)
                 ->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNotOnChannel(senderNickname, channelName));
  } else if (parameter.size() > 1 && changedTopic.empty() == false) {
    if (channel->isSetTopicOpOnlyChannel() == true &&
        serverParam.getChannel(channelName)->isOpClient(senderClient) ==
            false) {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.errChaNoPrivsNeeded(senderNickname, channelName));
    } else {
      channel->setTopic(changedTopic);
      commandResponse.addMultipleClientResponseMessage(
          channel->getAllClientFd(),
          this->replyMessage.successTopic(senderNickname, username, host,
                                          channelName, changedTopic));
    }
  } else {
    if (channel->getTopic().empty() == true) {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.rplNoTopic(senderNickname, channelName));
    } else {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.rplTopic(senderNickname, channelName,
                                      channel->getTopic()));
    }
  }
  return commandResponse;
}