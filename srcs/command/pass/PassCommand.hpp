#pragma once
#ifndef PASS_COMMAND_HPP
#define PASS_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class PassCommand : public ACommand {
 private:
  PassCommand(const PassCommand& other);
  PassCommand& operator=(const PassCommand& other);

 public:
  PassCommand();
  ~PassCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               ParsedParam& parsedParam);
};

#endif
