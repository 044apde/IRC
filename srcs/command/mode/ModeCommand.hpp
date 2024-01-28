#pragma once
#ifndef MODE_COMMAND_HPP
#define MODE_COMMAND_HPP

#include <cctype>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "../ACommand.hpp"
#include "../channel/Channel.hpp"
#include "../client/Client.hpp"
#include "../param/command_response_param/CommandResponseParam.hpp"
#include "../param/server_param/ServerParam.hpp"
#include "../param/token_param/TokenParam.hpp"

class ModeCommand : public ACommand {
 private:
  ModeCommand(const ModeCommand& other);
  ModeCommand& operator=(const ModeCommand& other);
  bool isValidSignedChar(const std::string& modeString, const size_t& index);
  bool isValidMode(const char& modeChar);
  bool isValidModeString(const std::string& modeString);
  bool isValidModeArgument(const std::vector<std::string>& parameter);
  bool isValidParamter(CommandResponseParam& commandResponse,
                       const TokenParam& tokenParam);
  size_t getArgumentSizeIndex(const std::string& argument);
  const std::string getSize_tMaxString();
  bool IsValidMaxUser(const std::string& argument);
  size_t getMaxUserParameter(const std::string& argument);
  bool executeMode(Client* client, Channel* channel,
                   const std::string& modeString,
                   std::vector<std::string> arguments);

 public:
  ModeCommand();
  ~ModeCommand();
  CommandResponseParam execute(ServerParam& serverParam,
                               const TokenParam& tokenParam);
};

#endif
