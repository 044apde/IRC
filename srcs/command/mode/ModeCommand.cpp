#include "ModeCommand.hpp"

ModeCommand::ModeCommand() : ACommand() {}

ModeCommand::~ModeCommand() {}

ModeCommand::ModeCommand(const ModeCommand &other) { static_cast<void>(other); }

ModeCommand &ModeCommand::operator=(const ModeCommand &other) {
  static_cast<void>(other);
  return *this;
}

// 모드에서 필요한 것은 다시 파싱할 때 받아오므로 그 때 다시 구현
CommandResponseParam ModeCommand::execute(ServerParam &serverParam,
                                          ParsedParam &parsedParam) {
  CommandResponseParam commandResponse;
  // int senderSocketFd = parsedParam.getSenderSocketFd();
  // std::string channelName = parsedParam.getChannel();
  // std::string nickname = parsedParam.getNickname();
  // char modeChar = parsedParam.getModeChar();
  // Channel *channel = serverParam.getChannel(channelName);
  // Client *client = serverParam.getClient(senderSocketFd);
  // Client *targetClient =
  //     serverParam.getClientByNickname(parsedParam.getNickname());

  // if (channelName.empty() == true) {
  //   commandResponse.setResponseMessage(
  //       this->replyMessage.errNeedMoreParams(parsedParam));
  // } else if (channel == NULL) {
  //   commandResponse.setResponseMessage(
  //       this->replyMessage.errNoSuchChannel(parsedParam));
  // } else if (channel->isClientInChannel(client) == false) {
  //   commandResponse.setResponseMessage(
  //       this->replyMessage.errNotOnChannel(parsedParam));
  // } else if (modeChar == '\0') {
  //   commandResponse.setResponseMessage(
  //       this->replyMessage.rplChannelModeIs(parsedParam, channel));
  // } else if (channel->isOpClient(client) == false) {
  //   commandResponse.setResponseMessage(
  //       this->replyMessage.errChaNoPrivsNeeded(parsedParam));
  // } else {
  //   // 임시 modestring 값 (실제로는 파싱에서 받아와야 함)
  //   std::string modestring = "itkol";
  //   std::string setttingModeString = "+";
  //   std::string unsettingModeString = "-";
  //   std::string modeParameter;

  //   for (size_t i = 0; i < modestring.size() &&
  //                      commandResponse.getResponseMessage().empty() == false;
  //        i++) {
  //     switch (modestring[i]) {
  //       case 'i':
  //         channel->setInviteOnly();
  //         break;
  //       case 't':
  //         channel->setTopicOpOnly();
  //         break;
  //       case 'k':
  //         if (channel->getChannelKey().empty() == false) {
  //           commandResponse.setResponseMessage(
  //               this->replyMessage.errKeySet(parsedParam));
  //           break;
  //         }
  //         channel->setKey(parsedParam.getPassword());
  //         break;
  //       case 'o':
  //         if (targetClient == NULL) {
  //           commandResponse.setResponseMessage(
  //               this->replyMessage.errNoSuchNick(parsedParam));
  //           break;
  //         }
  //         channel->setOpClient(targetClient);
  //         break;
  //       case 'l':
  //         if (channel->isSetMaxUserChannel() == true) {
  //           commandResponse.setResponseMessage(
  //               this->replyMessage.errChannelIsFull(parsedParam));
  //           break;
  //         }
  //         // 파라미터로 넘겨받아야 할 채널 최대 인원 수
  //         int maxUser = 10;
  //         // 최대 인원 수가 없을 경우 음수로 초기화 하기에 아래의 에러로
  //         처리? if (maxUser < 0) {
  //           commandResponse.setResponseMessage(
  //               this->replyMessage.errNeedMoreParams(parsedParam));
  //           break;
  //         }
  //         break;
  //       default:
  //         break;
  //     }
  //   }
  //   if (commandResponse.getTargetClientFdSet().empty() == true) {
  //     commandResponse.addTargetClientFd(senderSocketFd);
  //   }
  // }
  return commandResponse;
}