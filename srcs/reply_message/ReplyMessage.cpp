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

std::string ReplyMessage::rplNoTopic(const std::string& senderNickname,
                                     const std::string& channelName) {
  return "331 " + senderNickname + " " + channelName + " :No topic is set\r\n";
}

std::string ReplyMessage::rplTopic(const std::string& senderNickname,
                                   const std::string& channelName,
                                   const std::string& changedTopic,
                                   const std::string& curerntTopic) {
  return "332 " + senderNickname + " " + channelName + " :" +
         (curerntTopic.empty() == true ? changedTopic : curerntTopic) + "\r\n";
}

std::string ReplyMessage::rplInviting(const std::string& senderNickname,
                                      const std::string& invitedNickname,
                                      const std::string& channelName) {
  return "341 " + senderNickname + " " + invitedNickname + " " + channelName +
         "\r\n";
}

std::string ReplyMessage::rplNamReply(const std::string& senderNickname,
                                      const std::string& channelName,
                                      const std::string& nicknameList) {
  return "353 " + senderNickname + " = " + channelName + " " + nicknameList +
         "\r\n";
}

std::string ReplyMessage::errNoSuchNick(const std::string& senderNickname,
                                        const std::string& nickname) {
  return "401 " + senderNickname + " " + nickname +
         " :No such nick/channel\r\n";
}

std::string ReplyMessage::errNoSuchChannel(const std::string& senderNickname,
                                           const std::string& channelName) {
  return "403 " + senderNickname + " " + channelName + " :No such channel\r\n";
}

std::string ReplyMessage::errCannotSendToChan(const std::string& senderNickname,
                                              const std::string& channelName) {
  return "404 " + senderNickname + " " + channelName +
         " :Cannot send to channel\r\n";
}

std::string ReplyMessage::errTooManyChannels(const std::string& senderNickname,
                                             const std::string& channelName) {
  return "405 " + senderNickname + " " + channelName +
         " :You have joined too many "
         "channels\r\n";
}

std::string ReplyMessage::errNoOrigin(const std::string& senderNickname) {
  return "409 " + senderNickname + " :No origin specified\r\n";
}

std::string ReplyMessage::errNoRecipient(const std::string& senderNickname,
                                         const std::string& command) {
  return "411 " + senderNickname + " :No recipient given (" + command + ")\r\n";
}

std::string ReplyMessage::errNoTextToSend(const std::string& senderNickname) {
  return "412 " + senderNickname + " :No text to send\r\n";
}

std::string ReplyMessage::errUnknownCommand(const std::string& senderNickname,
                                            const std::string& command) {
  return "421 " + senderNickname + " " + command + " :Unknown command\r\n";
}

std::string ReplyMessage::errNoNicknameGiven(
    const std::string& senderNickname) {
  return "431 " + senderNickname + " :No nickname given\r\n";
}

std::string ReplyMessage::errErroneusNickname(const std::string& senderNickname,
                                              const std::string& nickname) {
  return "432 " + senderNickname + " " + nickname + " :Erroneus nickname\r\n";
}

std::string ReplyMessage::errNicknameInUse(const std::string& senderNickname,
                                           const std::string& nickname) {
  return "433 " + senderNickname + " " + nickname +
         " :Nickname is already in use\r\n";
}

std::string ReplyMessage::errUserNotInChannel(const std::string& targetNickname,
                                              const std::string& nickname,
                                              const std::string& channelName) {
  return "441 " + targetNickname + " " + nickname + " " + channelName +
         " :They aren't on that channel\r\n";
}

std::string ReplyMessage::errNotOnChannel(const std::string& senderNickname,
                                          const std::string& channelName) {
  return "442 " + senderNickname + " " + channelName +
         " :You're not on that channel\r\n";
}

std::string ReplyMessage::errUserOnChannel(const std::string& targetNickname,
                                           const std::string& channelName) {
  return "443 " + targetNickname + " " + channelName +
         " :is already on channel\r\n";
}

std::string ReplyMessage::errNotRegisterd(const std::string& senderNickname) {
  return "451 " +
         (senderNickname.empty() == false ? senderNickname : "unknown") +
         " :You have not registered\r\n";
}

std::string ReplyMessage::errNeedMoreParams(const std::string& senderNickname,
                                            const std::string& command) {
  return "461 " + senderNickname + " " + command +
         " :Not enough parameters\r\n";
}

std::string ReplyMessage::errAlreadyRegistered(
    const std::string& senderNickname) {
  return "462 " +
         (senderNickname.empty() == false ? senderNickname : "unknown") +
         " :You may not reregister\r\n";
}

std::string ReplyMessage::errPasswdMismatch(const std::string& senderNickname) {
  return "464 " +
         (senderNickname.empty() == false ? senderNickname : "unknown") +
         " :Password incorrect\r\n";
}

std::string ReplyMessage::errChannelIsFull(const std::string& senderNickname,
                                           const std::string& channelName) {
  return "471 " + senderNickname + " " + channelName +
         " :Cannot join channel (+l)\r\n";
}

std::string ReplyMessage::errUnknownMode(const std::string& senderNickname,
                                         const std::string& modeString) {
  return "472 " + senderNickname + " " + modeString +
         " :is unknown mode char to me\r\n";
}

std::string ReplyMessage::errInviteOnlyChan(const std::string& senderNickname,
                                            const std::string& channelName) {
  return "473 " + senderNickname + " " + channelName +
         " :Cannot join channel (+i)\r\n";
}

std::string ReplyMessage::errBadChannelKey(const std::string& senderNickname,
                                           const std::string& channelName) {
  return "475 " + senderNickname + " " + channelName +
         " :Cannot join channel (+k)\r\n";
}

std::string ReplyMessage::errChaNoPrivsNeeded(const std::string& senderNickname,
                                              const std::string& channelName) {
  return "482 " + senderNickname + " " + channelName +
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
                                      const std::string& username,
                                      const std::string& host,
                                      std::string reason) {
  if (reason.empty() == false) {
    reason = " " + reason;
  }
  return ":" + senderNickname + "!" + username + "@" + host + " QUIT" + reason +
         "\r\n";
}

std::string ReplyMessage::successTopic(const std::string& senderNickname,
                                       const std::string& channelName,
                                       const std::string& newTopic) {
  return ":" + senderNickname + " TOPIC " + channelName + " " + newTopic +
         "\r\n";
}
