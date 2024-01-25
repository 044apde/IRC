#pragma once
#ifndef PARSED_PARAM_BUILDER_HPP
#define PARSED_PARAM_BUILDER_HPP

#include <string>

#include "../parsed_param/ParsedParam.hpp"

class ParsedParamBuilder {
 private:
  int _senderSocketFd;
  std::string _command;
  std::string _serverPassword;
  std::string _channelKey;
  std::string _username;
  std::string _nickname;
  std::string _channelName;
  std::string _trailing;
  std::string _serverName;
  std::string _modeString;
  ParsedParamBuilder(const ParsedParamBuilder& other);
  ParsedParamBuilder& operator=(const ParsedParamBuilder& other);

 public:
  ParsedParamBuilder();
  ~ParsedParamBuilder();
  ParsedParamBuilder& senderSocketFd(const int _senderSocketFd);
  ParsedParamBuilder& command(const std::string& _command);
  ParsedParamBuilder& serverPassword(const std::string& _serverPassword);
  ParsedParamBuilder& channelKey(const std::string& _channelKey);
  ParsedParamBuilder& username(const std::string& _username);
  ParsedParamBuilder& nickname(const std::string& _nickname);
  ParsedParamBuilder& channelName(const std::string& _channelName);
  ParsedParamBuilder& trailing(const std::string& _trailing);
  ParsedParamBuilder& serverName(const std::string& _serverName);
  ParsedParamBuilder& modeString(const std::string& _modeString);
  ParsedParam build();
};

#endif
