#pragma once
#ifndef MODE_COMMAND_HPP
#define MODE_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class ModeCommand : public ACommand {
 private:
  ModeCommand(const ModeCommand& other);
  ModeCommand& operator=(const ModeCommand& other);

 public:
  ModeCommand();
  ~ModeCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               TokenParam& tokenParam);
};

#endif
