#pragma once
#ifndef PARSED_PARAM_BUILDER_HPP
#define PARSED_PARAM_BUILDER_HPP

#include <string>

#include "../parsed_param/ParsedParam.hpp"

class ParsedParamBuilder {
 private:
  int _senderSocketFd;
  std::string _fullMessage;
  std::string _command;
  std::string _password;
  std::string _username;
  std::string _nickname;
  std::string _channel;
  std::string _topic;
  char _modeChar;
  ParsedParamBuilder(const ParsedParamBuilder&);
  ParsedParamBuilder& operator=(const ParsedParamBuilder&);

 public:
  ParsedParamBuilder();
  ~ParsedParamBuilder();
  ParsedParamBuilder& senderSocketFd(const int senderSocketFd);
  ParsedParamBuilder& fullMessage(const std::string& fullMessage);
  ParsedParamBuilder& command(const std::string& command);
  ParsedParamBuilder& password(const std::string& password);
  ParsedParamBuilder& username(const std::string& username);
  ParsedParamBuilder& nickname(const std::string& nickname);
  ParsedParamBuilder& channel(const std::string& channel);
  ParsedParamBuilder& topic(const std::string& topic);
  ParsedParamBuilder& modeChar(const char& modeChar);
  ParsedParam build();
};

#endif
