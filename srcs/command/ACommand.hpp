#pragma once
#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include <string>

#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../reply_message/ReplyMessage.hpp"

class ACommand {
 private:
  ACommand(const ACommand& other);
  ACommand& operator=(const ACommand& other);

 protected:
  ACommand();
  ReplyMessage& replyMessage;

 public:
  virtual ~ACommand();
  virtual CommandResponseParam execute(ServerParam& serverParam,
                                       ParsedParam& parsedParam) = 0;
};

#endif
