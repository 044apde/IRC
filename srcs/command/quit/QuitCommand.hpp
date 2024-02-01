#pragma once
#ifndef QUIT_COMMAND_HPP
#define QUIT_COMMAND_HPP

#include <string>
#include <vector>

#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class QuitCommand : public ACommand {
 private:
  QuitCommand(const QuitCommand& other);
  QuitCommand& operator=(const QuitCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam,
                       const std::string& senderNickname);

 public:
  QuitCommand();
  ~QuitCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif