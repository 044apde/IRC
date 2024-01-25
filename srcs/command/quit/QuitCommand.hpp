#pragma once
#ifndef QUIT_COMMAND_HPP
#define QUIT_COMMAND_HPP

#include <string>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class QuitCommand : public ACommand {
 private:
  QuitCommand(const QuitCommand& other);
  QuitCommand& operator=(const QuitCommand& other);

 public:
  QuitCommand();
  ~QuitCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               ParsedParam& parsedParam);
};

#endif