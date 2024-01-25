#pragma once
#ifndef INVITE_COMMAND_HPP
#define INVITE_COMMAND_HPP

#include <cassert>
#include <string>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class InviteCommand : public ACommand {
 private:
  InviteCommand(const InviteCommand& other);
  InviteCommand& operator=(const InviteCommand& other);

 public:
  InviteCommand();
  ~InviteCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               TokenParam& tokenParam);
};

#endif
