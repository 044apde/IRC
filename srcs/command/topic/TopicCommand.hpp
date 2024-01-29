#pragma once
#ifndef TOPIC_COMMAND_HPP
#define TOPIC_COMMAND_HPP

#include <string>
#include <vector>

#include "../../channel/Channel.hpp"
#include "../../client/Client.hpp"
#include "../../param/command_response_param/CommandResponseParam.hpp"
#include "../../param/server_param/ServerParam.hpp"
#include "../../param/token_param/TokenParam.hpp"
#include "../ACommand.hpp"

class TopicCommand : public ACommand {
 private:
  TopicCommand(const TopicCommand& other);
  TopicCommand& operator=(const TopicCommand& other);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam);

 public:
  TopicCommand();
  ~TopicCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
