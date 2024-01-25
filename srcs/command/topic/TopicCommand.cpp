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

CommandResponseParam TopicCommand::execute(ServerParam& serverParam,
                                           ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;

  std::string channel = parsedParam.getChannelName();
  std::string topic = parsedParam.getTrailing();
  Client* client = serverParam.getClient(parsedParam.getSenderSocketFd());

  // 조건수정
  // 파라미터가 0개 일 때 errNeedMoreParams()
  if (channel.empty() == true || topic.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams(parsedParam));
  } else if (serverParam.getChannel(channel) == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel(parsedParam));
  } else if (topic.empty() == true) {
    // topic이 빈 문자열이면 topic을 삭제한다.
    // removeTopic(serverParam, parsedParam);
    // 채널 모든 사용자에게 topic이 변경되었다고 알린다.
  } else if (serverParam.getChannel(channel)->isClientInChannel(client) ==
             false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel(parsedParam));
  } else if (serverParam.getChannel(channel)->isOpClient(client) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded(parsedParam));
  }
  //   else {
  // if () {
  //     // rplNoTopic
  // } else {
  //     commandResponse.setResponseMessage(
  //         this->replyMessage.rplTopic(parsedParam, topic));
  //   }
  // 채널 모든 사용자에게 topic이 변경되었다고 알린다.
  // }
  return commandResponse;
}