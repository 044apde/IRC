#include "ReplyMessage.hpp"

ReplyMessage::ReplyMessage() {}

ReplyMessage::~ReplyMessage() {}

ReplyMessage::ReplyMessage(const ReplyMessage& src) { *this = src; }

ReplyMessage& ReplyMessage::operator=(const ReplyMessage& src) {
  static_cast<void>(src);
  return *this;
}

ReplyMessage& ReplyMessage::getInstance() {
  static ReplyMessage instance = ReplyMessage();
  return instance;
}

std::string ReplyMessage::rplWelcome(ParsedParam& parsedParam) {
  return "001 " + parsedParam.getUsername() +
         " :Welcome to the IRC42 Network " + parsedParam.getNickname() + "\r\n";
}

// IRC42 자리는 server name이 들어가는 곳
// 혹시나 클라이언트가 이에 대해 이해하지 못해 문제가 발생하면 수정 필요
std::string ReplyMessage::rplYourHost(ParsedParam& parsedParam) {
  return "002 " + parsedParam.getUsername() +
         " :Your host is IRC42, running version ircd42-1.0.0" + "\r\n";
}

std::string ReplyMessage::rplCreated(ParsedParam& parsedParam) {
  time_t now = time(0);
  tm* currentLocalTime = localtime(&now);
  std::string currentDatetime =
      std::to_string(currentLocalTime->tm_year + 1900) + "-" +
      std::to_string(currentLocalTime->tm_mon + 1) + "-" +
      std::to_string(currentLocalTime->tm_mday) + " " +
      std::to_string(currentLocalTime->tm_hour) + ":" +
      std::to_string(currentLocalTime->tm_min) + ":" +
      std::to_string(currentLocalTime->tm_sec);

  return "003 " + parsedParam.getUsername() + " :This server was created " +
         currentDatetime + "\r\n";
}

std::string ReplyMessage::rplMyInfo(ParsedParam& parsedParam) {
  return "004 " + parsedParam.getUsername() + " IRC42" + " ircd42-1.0.0" +
         "  " + " itkol \r\n";
}

std::string ReplyMessage::rplNoTopic(ParsedParam& parsedParam) {
  return "331 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :No topic is set\r\n";
}

std::string ReplyMessage::rplTopic(ParsedParam& parsedParam,
                                   const std::string& curerntTopic) {
  assert(curerntTopic.empty() == false ||
         parsedParam.getTrailing().empty() == false);
  return "332 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :" +
         (curerntTopic.empty() == true ? parsedParam.getTrailing()
                                       : curerntTopic) +
         "\r\n";
}

std::string ReplyMessage::rplInviting(ParsedParam& parsedParam) {
  return "341 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " " + parsedParam.getChannelName() + "\r\n";
}

std::string ReplyMessage::errNoSuchNick(ParsedParam& parsedParam) {
  return "401 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " :No such nick/channel\r\n";
}

std::string ReplyMessage::errNoSuchChannel(ParsedParam& parsedParam) {
  return "403 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :No such channel\r\n";
}

std::string ReplyMessage::errCannotSendToChan(ParsedParam& parsedParam) {
  return "404 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :Cannot send to channel\r\n";
}

std::string ReplyMessage::errTooManyChannels(ParsedParam& parsedParam) {
  return "405 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() +
         " :You have joined too many channels\r\n";
}

std::string ReplyMessage::errTooManyTargets(ParsedParam& parsedParam) {
  return "407 " + parsedParam.getUsername() + parsedParam.getNickname() +
         " :Too many recipients\r\n";
}

std::string ReplyMessage::errNoOrigin(ParsedParam& parsedParam) {
  return "409 " + parsedParam.getUsername() + " :No origin specified\r\n";
}

std::string ReplyMessage::errNoRecipient(ParsedParam& parsedParam) {
  return "411 " + parsedParam.getUsername() + " :No recipient given (" +
         parsedParam.getCommand() + ")\r\n";
}

std::string ReplyMessage::errNoTextToSend(ParsedParam& parsedParam) {
  return "412 " + parsedParam.getUsername() + " :No text to send\r\n";
}

std::string ReplyMessage::errUnknownCommand(ParsedParam& parsedParam) {
  return "421 " + parsedParam.getUsername() + " " + parsedParam.getCommand() +
         " :Unknown command\r\n";
}

std::string ReplyMessage::errNoNicknameGiven(ParsedParam& parsedParam) {
  return "431 " + parsedParam.getUsername() + " :No nickname given\r\n";
}

std::string ReplyMessage::errErroneusNickname(ParsedParam& parsedParam) {
  return "432 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " :Erroneus nickname\r\n";
}

std::string ReplyMessage::errNicknameInUse(ParsedParam& parsedParam) {
  return "433 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " :Nickname is already in use\r\n";
}

std::string ReplyMessage::errUserNotInChannel(ParsedParam& parsedParam) {
  return "441 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " " + parsedParam.getChannelName() +
         " :They aren't on that channel\r\n";
}

std::string ReplyMessage::errNotOnChannel(ParsedParam& parsedParam) {
  return "442 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :You're not on that channel\r\n";
}

std::string ReplyMessage::errUserOnChannel(ParsedParam& parsedParam) {
  return "443 " + parsedParam.getUsername() + " " + parsedParam.getNickname() +
         " " + parsedParam.getChannelName() + " :is already on channel\r\n";
}

std::string ReplyMessage::errNeedMoreParams(ParsedParam& parsedParam) {
  return "461 " + parsedParam.getUsername() + " " + parsedParam.getCommand() +
         " :Not enough parameters\r\n";
}

std::string ReplyMessage::errAlreadyRegistered(ParsedParam& parsedParam) {
  return "462 " + parsedParam.getUsername() + " :You may not reregister\r\n";
}

std::string ReplyMessage::errPasswdMismatch(ParsedParam& parsedParam) {
  return "464 " + parsedParam.getUsername() + " :Password incorrect\r\n";
}

std::string ReplyMessage::errKeySet(ParsedParam& parsedParam) {
  return "467 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :Channel key already set\r\n";
}

std::string ReplyMessage::errChannelIsFull(ParsedParam& parsedParam) {
  return "471 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :Cannot join channel (+l)\r\n";
}

std::string ReplyMessage::errUnknownMode(ParsedParam& parsedParam) {
  return "472 " + parsedParam.getUsername() + " " +
         parsedParam.getModeString() + " :is unknown mode char to me\r\n";
}

std::string ReplyMessage::errInviteOnlyChan(ParsedParam& parsedParam) {
  return "473 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :Cannot join channel (+i)\r\n";
}

std::string ReplyMessage::errBadChannelKey(ParsedParam& parsedParam) {
  return "475 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :Cannot join channel (+k)\r\n";
}

std::string ReplyMessage::errChaNoPrivsNeeded(ParsedParam& parsedParam) {
  return "482 " + parsedParam.getUsername() + " " +
         parsedParam.getChannelName() + " :You're not channel operator\r\n";
}

std::string ReplyMessage::successJoin(ParsedParam& parsedParam,
                                      const std::string& nickname) {
  return ":" + nickname + " JOIN " + parsedParam.getChannelName() + "\r\n";
}

std::string successKick(ParsedParam& parsedParam) {
  std::string comment = parsedParam.getTrailing();

  if (comment.empty() == false) {
    comment = " " + comment;
  }
  return "KICK " + parsedParam.getChannelName() + " " +
         parsedParam.getNickname() + comment + "\r\n";
}

std::string ReplyMessage::successPart(ParsedParam& parsedParam) {
  std::string reason = parsedParam.getTrailing();

  if (reason.empty() == false) {
    reason = " " + reason;
  }
  return "PART " + parsedParam.getChannelName() + reason + "\r\n";
}

std::string ReplyMessage::successPrivmsg(ParsedParam& parsedParam) {
  std::string target = parsedParam.getChannelName();

  if (target.empty() == true) {
    target = parsedParam.getNickname();
  }
  return "PRIVMSG " + target + " " + parsedParam.getTrailing() + "\r\n";
}

std::string ReplyMessage::successPing(ParsedParam& parsedParam) {
  return "PONG " + parsedParam.getServerName() + "\r\n";
}

std::string ReplyMessage::successQuit(ParsedParam& parsedParam) {
  std::string trailing = parsedParam.getTrailing();

  if (trailing.empty() == false) {
    trailing = " " + trailing;
  }
  return "QUIT" + trailing + "\r\n";
}
