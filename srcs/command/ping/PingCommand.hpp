#pragma once
#ifndef PING_COMMAND_HPP
#define PING_COMMAND_HPP

#include <string>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class PingCommand : public ACommand {
 private:
  PingCommand(const PingCommand& other);
  PingCommand& operator=(const PingCommand& other);

 public:
  PingCommand();
  ~PingCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               ParsedParam& parsedParam);
};

#endif