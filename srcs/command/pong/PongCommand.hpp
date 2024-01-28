#pragma once
#ifndef PONG_COMMAND_HPP
#define PONG_COMMAND_HPP

#include <string>
#include <vector>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../param/token_param/TokenParam.hpp"

class PongCommand : public ACommand {
 private:
  PongCommand(const PongCommand& other);
  PongCommand& operator=(const PongCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam);

 public:
  PongCommand();
  ~PongCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif