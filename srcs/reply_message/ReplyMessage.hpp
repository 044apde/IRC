#pragma once
#ifndef REPLY_MESSAGE_HPP
#define REPLY_MESSAGE_HPP

#include <ctime>
#include <string>
#include <vector>

class ReplyMessage {
 private:
  ReplyMessage();
  ~ReplyMessage();
  ReplyMessage(const ReplyMessage& src);
  ReplyMessage& operator=(const ReplyMessage& src);
  const std::string getCurrentDatetime();

 public:
  static ReplyMessage& getInstance();
  std::string rplWelcome(const std::string& senderNickname);
  std::string rplYourHost(const std::string& senderNickname);
  std::string rplCreated(const std::string& senderNickname);
  std::string rplMyInfo(const std::string& senderNickname);
  std::string rplNoTopic(const std::string& channelName);
  std::string rplTopic(const std::string& channelName,
                       const std::string& changedTopic,
                       const std::string& curerntTopic);
  std::string rplInviting(const std::string& username,
                          const std::string& nickname,
                          const std::string& channelName);
  std::string rplNamReply(const std::string& targetNickname,
                          const std::string& channelName,
                          const std::string& nicknameList);
  std::string errUnknownError(const std::string& command,
                              const std::string& info);
  std::string errNoSuchNick(const std::string& username,
                            const std::string& nickname);
  std::string errNoSuchChannel(const std::string& username,
                               const std::string& channelName);
  std::string errCannotSendToChan(const std::string& username,
                                  const std::string& channelName);
  std::string errTooManyChannels(const std::string& username,
                                 const std::string& channelName);
  std::string errTooManyTargets(const std::string& channelName);
  std::string errNoOrigin(const std::string& username);
  std::string errNoRecipient(const std::string& username,
                             const std::string& command);
  std::string errNoTextToSend(const std::string& username);
  std::string errInputTooLong(const std::string& username);
  std::string errUnknownCommand(const std::string& username,
                                const std::string& command);
  std::string errNoNicknameGiven(const std::string& username);
  std::string errErroneusNickname(const std::string& nickname);
  std::string errNicknameInUse(const std::string& username,
                               const std::string& nickname);
  std::string errUserNotInChannel(const std::string& username,
                                  const std::string& nickname,
                                  const std::string& channelName);
  std::string errNotOnChannel(const std::string& username,
                              const std::string& channelName);
  std::string errUserOnChannel(const std::string& username,
                               const std::string& nickname,
                               const std::string& channelName);
  std::string errNotRegisterd();
  std::string errNeedMoreParams(const std::string& username,
                                const std::string& command);
  std::string errAlreadyRegistered(const std::string& username);
  std::string errPasswdMismatch(const std::string& username);
  std::string errKeySet(const std::string& username,
                        const std::string& channelName);
  std::string errChannelIsFull(const std::string& username,
                               const std::string& channelName);
  std::string errUnknownMode(const std::string& username,
                             const std::string& modeString);
  std::string errInviteOnlyChan(const std::string& username,
                                const std::string& channelName);
  std::string errBadChannelKey(const std::string& username,
                               const std::string& channelName);
  std::string errChaNoPrivsNeeded(const std::string& username,
                                  const std::string& channelName);
  std::string successInvite(const std::string& senderNickname,
                            const std::string& channelName,
                            const std::string& targetNickname);
  std::string successJoin(const std::string& senderNickname,
                          const std::string& channelName);
  std::string successKick(const std::string& senderNickname,
                          const std::string& channelName,
                          const std::string& targetNickname,
                          std::string comment);
  std::string successMode(const std::string& senderNickname,
                          const std::string& targetName,
                          const std::string& modeString,
                          std::vector<std::string> argument);
  std::string successNick(std::string senderNickname,
                          const std::string& newNickname);
  std::string successPart(const std::string& senderNickname,
                          const std::string& channelName, std::string reason);
  std::string successPing(const std::string& serverName);
  std::string successPrivmsg(const std::string& senderNickname,
                             const std::string& targetNickOrChannel,
                             const std::string& message);
  std::string successQuit(const std::string& senderNickname,
                          std::string reason);
  std::string successTopic(const std::string& senderNickname,
                           const std::string& channelName,
                           const std::string& newTopic);
};

#endif
