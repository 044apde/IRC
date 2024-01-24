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
  if (client->getChannelVecSize() >= 10) {
    return true;
  }
  return false;
}

CommandResponseParam JoinCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;
  std::string channelName = parsedParam.getChannel();
  Client* client = serverParam.getClient(parsedParam.getSenderSocketFd());
  Channel* channel = serverParam.getChannel(channelName);

  if (channelName.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (channel == NULL) {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.errTooManyChannels(parsedParam));
    } else {
      channel = new Channel(channelName);
      serverParam.addChannel(channelName, client);
      commandResponse.setResponseMessage(
          this->replyMessage.successJoin(parsedParam, client->getNickname()));
    }
  } else if (channel->isSetKeyChannel() == true &&
             isInValidChannelKey(parsedParam.getChannelKey(),
                                 channel->getChannelKey()) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errBadChannelKey(parsedParam));
  } else if (channel->isChannelFull() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChannelIsFull(parsedParam));
  } else if (channel->isClientInChannel(client) == true) {
    // TODO: 정의되지 않은 상황이지만 nc명령으론 가능한 것
    // UB로 두고, 나중에 회의 후 삭제 또는 구현 방식 결정
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isClientInvited(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errInviteOnlyChan(parsedParam));
  } else {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.setResponseMessage(
          this->replyMessage.errTooManyChannels(parsedParam));
    } else {
      client->addChannel(channel);
      channel->addClient(client);
      commandResponse.setResponseMessage(
          this->replyMessage.successJoin(parsedParam, client->getNickname()) +
          (channel->getTopic().empty() == true
               ? ""
               : this->replyMessage.rplTopic(parsedParam,
                                             channel->getTopic())));
    }
  }
  return commandResponse;
}