#pragma once
#ifndef PONG_COMMAND_HPP
#define PONG_COMMAND_HPP

#include <string>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class PongCommand : public ACommand {
 private:
  PongCommand(const PongCommand& other);
  PongCommand& operator=(const PongCommand& other);

 public:
  PongCommand();
  ~PongCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               TokenParam& tokenParam);
};

#endif