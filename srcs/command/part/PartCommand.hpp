#pragma once
#ifndef PART_COMMAND_HPP
#define PART_COMMAND_HPP

#include <string>
#include <vector>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class PartCommand : public ACommand {
 private:
  PartCommand(const PartCommand& other);
  PartCommand& operator=(const PartCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam,
                       const std::string& senderNickname);

 public:
  PartCommand();
  ~PartCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
