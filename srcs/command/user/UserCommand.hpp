#pragma once
#ifndef USER_COMMAND_HPP
#define USER_COMMAND_HPP

#include <string>
#include <vector>

#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class UserCommand : public ACommand {
 private:
  UserCommand(const UserCommand &other);
  UserCommand &operator=(const UserCommand &other);
  bool isValidParamter(CommandResponseParam &commandResponse,
                       const TokenParam &tokenParam);

 public:
  UserCommand();
  ~UserCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               const TokenParam &tokenParam);
};

#endif
