#pragma once
#ifndef PING_COMMAND_HPP
#define PING_COMMAND_HPP

#include <string>
#include <vector>

#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class PingCommand : public ACommand {
 private:
  PingCommand(const PingCommand& other);
  PingCommand& operator=(const PingCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam,
                       const std::string& senderNickname);

 public:
  PingCommand();
  ~PingCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif