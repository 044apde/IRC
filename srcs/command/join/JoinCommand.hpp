#pragma once
#ifndef JOIN_COMMAND_HPP
#define JOIN_COMMAND_HPP

#include <string>
#include <vector>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class JoinCommand : public ACommand {
 private:
  JoinCommand(const JoinCommand& other);
  JoinCommand& operator=(const JoinCommand& other);
  bool isInValidChannelKey(const std::string& parsedChannelKey,
                           const std::string& channelKey) const;
  bool isClientChannelSizeOver(Client* client) const;
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam);

 public:
  JoinCommand();
  ~JoinCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
