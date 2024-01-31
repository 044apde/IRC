#include "ReplyMessage.hpp"

ReplyMessage::ReplyMessage() {}

ReplyMessage::~ReplyMessage() {}

ReplyMessage::ReplyMessage(const ReplyMessage& src) { *this = src; }

ReplyMessage& ReplyMessage::operator=(const ReplyMessage& src) {
  static_cast<void>(src);
  return *this;
}

const std::string ReplyMessage::getCurrentDatetime() {
  const time_t now = std::time(NULL);
  const struct tm* timeinfo = std::localtime(&now);
  char buffer[20];

  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return std::string(buffer);
}

ReplyMessage& ReplyMessage::getInstance() {
  static ReplyMessage instance = ReplyMessage();
  return instance;
}

std::string ReplyMessage::rplWelcome(const std::string& senderNickname) {
  return "001 " + senderNickname + " :Welcome to the IRC42 Network " +
         senderNickname + "\r\n";
}

// IRC42 자리는 server name이 들어가는 곳
// 혹시나 클라이언트가 이에 대해 이해하지 못해 문제가 발생하면 수정 필요
std::string ReplyMessage::rplYourHost(const std::string& senderNickname) {
  return "002 " + senderNickname +
         " :Your host is IRC42, running version ircd42-1.0.0" + "\r\n";
}

std::string ReplyMessage::rplCreated(const std::string& senderNickname) {
  const std::string currentDatetime = getCurrentDatetime();

  return "003 " + senderNickname + " :This server was created " +
         currentDatetime + "\r\n";
}

std::string ReplyMessage::rplMyInfo(const std::string& senderNickname) {
  return "004 " + senderNickname + " IRC42" + " ircd42-1.0.0" + " -" +
         " itkol \r\n";
}

std::string ReplyMessage::rplNoTopic(const std::string& channelName) {
  return "331 IRC42 " + channelName + " :No topic is set\r\n";
}

std::string ReplyMessage::rplTopic(const std::string& channelName,
                                   const std::string& changedTopic,
                                   const std::string& curerntTopic) {
  return "332 IRC42 " + channelName + " :" +
         (curerntTopic.empty() == true ? changedTopic : curerntTopic) + "\r\n";
}

std::string ReplyMessage::rplInviting(const std::string& invitedNickname,
                                      const std::string& channelName) {
  return "341 IRC42 " + invitedNickname + " " + channelName + "\r\n";
}

std::string ReplyMessage::rplNamReply(const std::string& targetNickname,
                                      const std::string& channelName,
                                      const std::string& nicknameList) {
  return "353 " + targetNickname + " = " + channelName + " " + nicknameList +
         "\r\n";
}

std::string ReplyMessage::errUnknownError(const std::string& command,
                                          const std::string& info) {
  return "400 " + command + " :" + info + "\r\n";
}

std::string ReplyMessage::errNoSuchNick(const std::string& username,
                                        const std::string& nickname) {
  return "401 " + username + " " + nickname + " :No such nick/channel\r\n";
}

std::string ReplyMessage::errNoSuchChannel(const std::string& username,
                                           const std::string& channelName) {
  return "403 " + username + " " + channelName + " :No such channel\r\n";
}

std::string ReplyMessage::errCannotSendToChan(const std::string& username,
                                              const std::string& channelName) {
  return "404 " + username + " " + channelName + " :Cannot send to channel\r\n";
}

std::string ReplyMessage::errTooManyChannels(const std::string& username,
                                             const std::string& channelName) {
  return "405 " + username + " " + channelName +
         " :You have joined too many "
         "channels\r\n";
}

std::string ReplyMessage::errTooManyTargets(const std::string& nickname) {
  return "407 " + nickname + " :Duplicate recipients No message delevered\r\n";
}

std::string ReplyMessage::errNoOrigin(const std::string& username) {
  return "409 " + username + " :No origin specified\r\n";
}

std::string ReplyMessage::errNoRecipient(const std::string& username,
                                         const std::string& command) {
  return "411 " + username + " :No recipient given (" + command + ")\r\n";
}

std::string ReplyMessage::errNoTextToSend(const std::string& username) {
  return "412 " + username + " :No text to send\r\n";
}

std::string ReplyMessage::errInputTooLong(const std::string& username) {
  return "414 " + username + " :Input line too long\r\n";
}

std::string ReplyMessage::errUnknownCommand(const std::string& username,
                                            const std::string& command) {
  return "421 " + username + " " + command + " :Unknown command\r\n";
}

std::string ReplyMessage::errNoNicknameGiven(const std::string& username) {
  return "431 " + username + " :No nickname given\r\n";
}

std::string ReplyMessage::errErroneusNickname(const std::string& nickname) {
  return "432 IRC42 " + nickname + " :Erroneus nickname\r\n";
}

std::string ReplyMessage::errNicknameInUse(const std::string& username,
                                           const std::string& nickname) {
  return "433 " + username + " " + nickname +
         " :Nickname is already in use\r\n";
}

std::string ReplyMessage::errUserNotInChannel(const std::string& username,
                                              const std::string& nickname,
                                              const std::string& channelName) {
  return "441 " + username + " " + nickname + " " + channelName +
         " :They aren't on that channel\r\n";
}

std::string ReplyMessage::errNotOnChannel(const std::string& username,
                                          const std::string& channelName) {
  return "442 " + username + " " + channelName +
         " :You're not on that channel\r\n";
}

std::string ReplyMessage::errUserOnChannel(const std::string& targetNickname,
                                           const std::string& channelName) {
  return "443 " + targetNickname + " " + channelName + " :is already on channel\r\n";
}

std::string ReplyMessage::errNotRegisterd() {
  return "451 :You have not registered\r\n";
}

std::string ReplyMessage::errNeedMoreParams(const std::string& username,
                                            const std::string& command) {
  return "461 " + username + " " + command + " :Not enough parameters\r\n";
}

std::string ReplyMessage::errAlreadyRegistered(const std::string& username) {
  return "462 " + username + " :You may not reregister\r\n";
}

std::string ReplyMessage::errPasswdMismatch(const std::string& username) {
  return "464 " + username + " :Password incorrect\r\n";
}

std::string ReplyMessage::errKeySet(const std::string& username,
                                    const std::string& channelName) {
  return "467 " + username + " " + channelName +
         " :Channel key already set\r\n";
}

std::string ReplyMessage::errChannelIsFull(const std::string& username,
                                           const std::string& channelName) {
  return "471 " + username + " " + channelName +
         " :Cannot join channel (+l)\r\n";
}

std::string ReplyMessage::errUnknownMode(const std::string& username,
                                         const std::string& modeString) {
  return "472 " + username + " " + modeString +
         " :is unknown mode char to me\r\n";
}

std::string ReplyMessage::errInviteOnlyChan(const std::string& username,
                                            const std::string& channelName) {
  return "473 " + username + " " + channelName +
         " :Cannot join channel (+i)\r\n";
}

std::string ReplyMessage::errBadChannelKey(const std::string& username,
                                           const std::string& channelName) {
  return "475 " + username + " " + channelName +
         " :Cannot join channel (+k)\r\n";
}

std::string ReplyMessage::errChaNoPrivsNeeded(const std::string& username,
                                              const std::string& channelName) {
  return "482 " + username + " " + channelName +
         " :You're not channel operator\r\n";
}

std::string ReplyMessage::successInvite(const std::string& senderNickname,
                                        const std::string& channelName,
                                        const std::string& host,
                                        const std::string& username,
                                        const std::string& targetNickname) {
  return ":" + senderNickname + "!" + username + "@" + host + " INVITE " +
         targetNickname + " " + channelName + "\r\n";
}

std::string ReplyMessage::successJoin(const std::string& senderNickname,
                                      const std::string& username,
                                      const std::string& host,
                                      const std::string& channelName) {
  return ":" + senderNickname + "!" + username + "@" + host + " JOIN " +
         channelName + "\r\n";
}

std::string ReplyMessage::successKick(const std::string& senderNickname,
                                      const std::string& username,
                                      const std::string& host,
                                      const std::string& channelName,
                                      const std::string& targetNickname,
                                      std::string comment) {
  if (comment.empty() == false) {
    comment = " " + comment;
  }
  return ":" + senderNickname + "!" + username + "@" + host + " KICK " +
         channelName + " " + targetNickname + comment + "\r\n";
}

std::string ReplyMessage::successMode(const std::string& senderNickname,
                                      const std::string& username,
                                      const std::string& host,
                                      const std::string& targetName,
                                      const std::string& modeString,
                                      std::vector<std::string> argument) {
  std::string argumentsString;

  for (size_t i = 0; i < argument.size(); i++) {
    argumentsString += " " + argument[i];
  }

  return ":" + senderNickname + "!" + username + "@" + host + " MODE " +
         targetName + " " + modeString + argumentsString + "\r\n";
}

std::string ReplyMessage::successNick(std::string senderNickname,
                                      const std::string& username,
                                      const std::string& host,
                                      const std::string& newNickname) {
  if (senderNickname.empty() == false) {
    senderNickname = ":" + senderNickname;
  }
  return senderNickname + "!" + username + "@" + host + " NICK " + newNickname +
         "\r\n";
}

std::string ReplyMessage::successPart(const std::string& senderNickname,
                                      const std::string& username,
                                      const std::string& host,
                                      const std::string& channelName,
                                      std::string reason) {
  if (reason.empty() == false) {
    reason = " " + reason;
  }
  return ":" + senderNickname + "!" + username + "@" + host + " PART " +
         channelName + reason + "\r\n";
}

std::string ReplyMessage::successPing(const std::string& serverName) {
  return "PONG " + serverName + "\r\n";
}

std::string ReplyMessage::successPrivmsg(const std::string& senderNickname,
                                         const std::string& targetNickOrChannel,
                                         const std::string& message) {
  return ":" + senderNickname + " PRIVMSG " + targetNickOrChannel + " " +
         message + "\r\n";
}

std::string ReplyMessage::successQuit(const std::string& senderNickname,
                                      std::string reason) {
  if (reason.empty() == false) {
    reason = " " + reason;
  }
  return ":" + senderNickname + " QUIT" + reason + "\r\n";
}

std::string ReplyMessage::successTopic(const std::string& senderNickname,
                                       const std::string& channelName,
                                       const std::string& newTopic) {
  return ":" + senderNickname + " TOPIC " + channelName + " " + newTopic +
         "\r\n";
}
