#pragma once
#ifndef REPLY_MESSAGE_HPP
#define REPLY_MESSAGE_HPP

#include <cassert>
#include <ctime>
#include <string>

#include "../param/parsed_param/ParsedParam.hpp"

class ReplyMessage {
 private:
  ReplyMessage();
  ~ReplyMessage();
  ReplyMessage(const ReplyMessage& src);
  ReplyMessage& operator=(const ReplyMessage& src);

 public:
  static ReplyMessage& getInstance();
  std::string rplWelcome(ParsedParam& parsedParam);
  std::string rplYourHost(ParsedParam& parsedParam);
  std::string rplCreated(ParsedParam& parsedParam);
  std::string rplMyInfo(ParsedParam& parsedParam);
  std::string rplNoTopic(ParsedParam& parsedParam);
  std::string rplTopic(ParsedParam& parsedParam, const std::string& topic);
  std::string rplInviting(ParsedParam& parsedParam);
  std::string errNoSuchNick(ParsedParam& parsedParam);
  std::string errNoSuchChannel(ParsedParam& parsedParam);
  std::string errCanNotSendToChan(ParsedParam& parsedParam);
  std::string errTooManyChannels(ParsedParam& parsedParam);
  std::string errTooManyTargets(ParsedParam& parsedParam);
  std::string errNoOrigin(ParsedParam& parsedParam);
  std::string errNoRecipient(ParsedParam& parsedParam);
  std::string errNoTextToSend(ParsedParam& parsedParam);
  std::string errUnknownCommand(ParsedParam& parsedParam);
  std::string errNoNicknameGiven(ParsedParam& parsedParam);
  std::string errErroneusNickname(ParsedParam& parsedParam);
  std::string errNicknameInUse(ParsedParam& parsedParam);
  std::string errNotOnChannel(ParsedParam& parsedParam);
  std::string errUserNoChannel(ParsedParam& parsedParam);
  std::string errNeedMoreParams(ParsedParam& parsedParam);
  std::string errAlreadyRegistered(ParsedParam& parsedParam);
  std::string errPasswdMismatch(ParsedParam& parsedParam);
  std::string errKeySet(ParsedParam& parsedParam);
  std::string errChannelIsFull(ParsedParam& parsedParam);
  std::string errUnknownMode(ParsedParam& parsedParam);
  std::string errInviteOnlyChan(ParsedParam& parsedParam);
  std::string errBadChannelKey(ParsedParam& parsedParam);
  std::string errChaNoPrivsNeeded(ParsedParam& parsedParam);
  std::string successJoin(ParsedParam& parsedParam,
                          const std::string& nickname);
};

#endif
