#pragma once
#ifndef TOPIC_COMMAND_HPP
#define TOPIC_COMMAND_HPP

#include <string>

#include "../../client/Client.hpp"
#include "../ACommand.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class TopicCommand : public ACommand {
 private:
  TopicCommand(const TopicCommand& other);
  TopicCommand& operator=(const TopicCommand& other);

 public:
  TopicCommand();
  ~TopicCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               ParsedParam& parsedParam);
};

#endif
