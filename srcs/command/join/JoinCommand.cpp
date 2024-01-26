#include "JoinCommand.hpp"

JoinCommand::JoinCommand() : ACommand() {}

JoinCommand::~JoinCommand() {}

JoinCommand::JoinCommand(const JoinCommand& other) { static_cast<void>(other); }

JoinCommand& JoinCommand::operator=(const JoinCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool JoinCommand::isInValidChannelKey(const std::string& parsedChannelKey,
                                      const std::string& channelKey) const {
  if (channelKey.empty() == true || parsedChannelKey != channelKey) {
    return true;
  }
  return false;
}

bool JoinCommand::isClientChannelSizeOver(Client* client) const {
  if (client->getChannelSetSize() >= 10) {
    return true;
  }
  return false;
}

bool JoinCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true) {
    return false;
  }
  return true;
}

CommandResponseParam JoinCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  const std::string& channelName = parameter[0];
  Client* client = serverParam.getClient(senderSocketFd);
  const std::string& nickname = client->getNickname();
  Channel* channel = serverParam.getChannel(channelName);

  if (isRegisteredClient(client) == false) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.errTooManyChannels("", channelName));
    } else {
      channel = new Channel(channelName);
      serverParam.addNewChannel(channelName, client);
      commandResponse.setResponseMessage(
          this->replyMessage.successJoin(nickname, channelName));
    }
  } else if (channel->isSetKeyChannel() == true &&
             (parameter.size() < 2 ||
              isInValidChannelKey(parameter[1], channel->getChannelKey()) ==
                  true)) {
    commandResponse.setResponseMessage(
        this->replyMessage.errBadChannelKey("", channelName));
  } else if (channel->isChannelFull() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChannelIsFull("", channelName));
  } else if (channel->isClientInChannel(client) == true) {
    // TODO: 정의되지 않은 상황이지만 nc명령으론 가능한 것
    // UB로 두고, 나중에 회의 후 삭제 또는 구현 방식 결정
    commandResponse.setResponseMessage(
        this->replyMessage.errUserOnChannel("", nickname, channelName));
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isClientInvited(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errInviteOnlyChan("", channelName));
  } else {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.errTooManyChannels("", channelName));
    } else {
      serverParam.addClientAndChannelEachOther(client, channel);
      commandResponse.setResponseMessage(
          this->replyMessage.successJoin(nickname, channelName) +
          (channel->getTopic().empty() == true
               ? ""
               : this->replyMessage.rplTopic("", channelName, "",
                                             channel->getTopic())));
      channel->setAllClientFd(commandResponse.getTargetClientFdSet());
    }
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}