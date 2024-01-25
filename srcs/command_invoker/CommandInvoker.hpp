#pragma once
#ifndef COMMAND_INVOKER_HPP
#define COMMAND_INVOKER_HPP

#include <map>
#include <string>

#include "../command/invite/InviteCommand.hpp"
#include "../command/join/JoinCommand.hpp"
#include "../command/kick/KickCommand.hpp"
#include "../command/mode/ModeCommand.hpp"
#include "../command/nick/NickCommand.hpp"
#include "../command/part/PartCommand.hpp"
#include "../command/pass/PassCommand.hpp"
#include "../command/ping/PingCommand.hpp"
#include "../command/pong/PongCommand.hpp"
#include "../command/privmsg/PrivmsgCommand.hpp"
#include "../command/quit/QuitCommand.hpp"
#include "../command/topic/TopicCommand.hpp"
#include "../command/user/UserCommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/parsed_param_builder/ParsedParamBuilder.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../param/token_param/TokenParam.hpp"
#include "../reply_message/ReplyMessage.hpp"

class CommandInvoker {
 private:
  ReplyMessage& replyMessage;
  std::map<std::string, ACommand*> commandMap;
  CommandInvoker(const CommandInvoker& other);
  CommandInvoker& operator=(const CommandInvoker& other);

 public:
  CommandInvoker();
  ~CommandInvoker();
  CommandResponseParam execute(ServerParam& serverParam,
                               TokenParam& tokenParam);
};

#endif
