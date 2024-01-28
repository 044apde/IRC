#pragma once
#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include <string>
#include <vector>

#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../param/token_param/TokenParam.hpp"
#include "../reply_message/ReplyMessage.hpp"

class ACommand {
 private:
  ACommand(const ACommand& other);
  ACommand& operator=(const ACommand& other);

 protected:
  ACommand();
  ReplyMessage& replyMessage;
  bool isValidNickname(const std::string& nickname);
  bool isValidChannelName(const std::string& channelName);
  bool isRegisteredClient(Client* client);
  bool isTrailing(const std::string& str);
  virtual bool isValidParamter(CommandResponseParam& commandResponse,
                               const TokenParam& tokenParam) = 0;

 public:
  virtual ~ACommand();
  virtual CommandResponseParam execute(ServerParam& serverParam,
                                       const TokenParam& tokenParam) = 0;
};

#endif