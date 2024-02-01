#pragma once
#ifndef KICK_COMMAND_HPP
#define KICK_COMMAND_HPP

#include <string>
#include <vector>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class KickCommand : public ACommand {
 private:
  KickCommand(const KickCommand &other);
  KickCommand &operator=(const KickCommand &other);
  bool isValidParamter(CommandResponseParam &commandResponse,
                       const TokenParam &tokenParam,
                       const std::string &senderNickname);

 public:
  KickCommand();
  ~KickCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               const TokenParam &tokenParam);
};

#endif
