#pragma once
#ifndef PRIVMSG_COMMAND_HPP
#define PRIVMSG_COMMAND_HPP

#include <string>
#include <vector>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class PrivmsgCommand : public ACommand {
 private:
  PrivmsgCommand(const PrivmsgCommand &other);
  PrivmsgCommand &operator=(const PrivmsgCommand &other);
  bool isValidParamter(CommandResponseParam &commandResponse,
                       const TokenParam &tokenParam);

 public:
  PrivmsgCommand();
  ~PrivmsgCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               const TokenParam &tokenParam);
};

#endif
