#pragma once
#ifndef PART_COMMAND_HPP
#define PART_COMMAND_HPP

#include <string>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class PartCommand : public ACommand {
 private:
  PartCommand(const PartCommand& other);
  PartCommand& operator=(const PartCommand& other);

 public:
  PartCommand();
  ~PartCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               TokenParam& tokenParam);
};

#endif
