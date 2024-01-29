#pragma once
#ifndef NICK_COMMAND_HPP
#define NICK_COMMAND_HPP

#include <cctype>
#include <string>
#include <vector>

#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class NickCommand : public ACommand {
 private:
  NickCommand(const NickCommand &other);
  NickCommand &operator=(const NickCommand &other);
  bool isValidParamter(CommandResponseParam &commandResponse,
                       const TokenParam &tokenParam);

 public:
  NickCommand();
  ~NickCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               const TokenParam &tokenParam);
};

#endif
