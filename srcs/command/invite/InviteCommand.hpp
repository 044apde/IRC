#pragma once
#ifndef INVITE_COMMAND_HPP
#define INVITE_COMMAND_HPP

#include <string>
#include <vector>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class InviteCommand : public ACommand {
 private:
  InviteCommand(const InviteCommand& other);
  InviteCommand& operator=(const InviteCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam,
                       const std::string& senderNickname);

 public:
  InviteCommand();
  ~InviteCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
