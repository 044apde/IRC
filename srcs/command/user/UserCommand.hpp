#pragma once
#ifndef USER_COMMAND_HPP
#define USER_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class UserCommand : public ACommand {
 private:
  UserCommand(const UserCommand &other);
  UserCommand &operator=(const UserCommand &other);

 public:
  UserCommand();
  ~UserCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               ParsedParam &parsedParam);
};

#endif
