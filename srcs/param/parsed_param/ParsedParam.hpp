#pragma once
#ifndef PARSED_PARAM_HPP
#define PARSED_PARAM_HPP

#include <string>

class ParsedParam {
 private:
  const int senderSocketFd;
  const std::string command;
  const std::string serverPassword;
  const std::string channelKey;
  const std::string username;
  const std::string nickname;
  const std::string channelName;
  const std::string trailing;
  const std::string serverName;
  const std::string modeString;
  ParsedParam();

 public:
  ParsedParam(const int& senderSocketFd, const std::string& command,
              const std::string& serverPassword, const std::string& channelKey,
              const std::string& username, const std::string& nickname,
              const std::string& channelName, const std::string& trailing,
              const std::string& serverName, const std::string& modeString);
  ParsedParam(const ParsedParam& other);
  ParsedParam& operator=(const ParsedParam& other);
  ~ParsedParam();
  const int& getSenderSocketFd();
  const std::string& getCommand();
  const std::string& getServerPassword();
  const std::string& getChannelKey();
  const std::string& getUsername();
  const std::string& getNickname();
  const std::string& getChannelName();
  const std::string& getTrailing();
  const std::string& getServerName();
  const std::string& getModeString();
};

#endif