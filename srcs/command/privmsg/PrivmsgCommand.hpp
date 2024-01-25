#pragma once
#ifndef PRIVMSG_COMMAND_HPP
#define PRIVMSG_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class PrivmsgCommand : public ACommand {
 private:
  PrivmsgCommand(const PrivmsgCommand &other);
  PrivmsgCommand &operator=(const PrivmsgCommand &other);

 public:
  PrivmsgCommand();
  ~PrivmsgCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               ParsedParam &parsedParam);
};

#endif
