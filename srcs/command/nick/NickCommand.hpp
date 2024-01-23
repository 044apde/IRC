#pragma once
#ifndef NICK_COMMAND_HPP
#define NICK_COMMAND_HPP

#include <cctype>
#include <string>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class NickCommand : public ACommand {
 private:
  NickCommand(const NickCommand &other);
  NickCommand &operator=(const NickCommand &other);
  bool isInvalidNickname(const std::string &nickname) const;
  bool isSameStrWithLowercase(const std::string &str1,
                              const std::string &str2) const;

 public:
  NickCommand();
  ~NickCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               ParsedParam &parsedParam) = 0;
};

#endif
