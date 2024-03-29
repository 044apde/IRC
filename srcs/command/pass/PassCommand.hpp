#pragma once
#ifndef PASS_COMMAND_HPP
#define PASS_COMMAND_HPP

#include <string>
#include <vector>

#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class PassCommand : public ACommand {
 private:
  PassCommand(const PassCommand& other);
  PassCommand& operator=(const PassCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam,
                       const std::string& senderNickname);

 public:
  PassCommand();
  ~PassCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
