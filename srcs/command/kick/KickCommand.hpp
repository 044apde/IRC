#pragma once
#ifndef KICK_COMMAND_HPP
#define KICK_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class KickCommand : public ACommand {
 private:
  KickCommand(const KickCommand &other);
  KickCommand &operator=(const KickCommand &other);

 public:
  KickCommand();
  ~KickCommand();
  CommandResponseParam execute(ServerParam &serverParam,
                               ParsedParam &parsedParam);
};

#endif
