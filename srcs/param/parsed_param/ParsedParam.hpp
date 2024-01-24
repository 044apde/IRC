#pragma once
#ifndef PARSED_PARAM_HPP
#define PARSED_PARAM_HPP

#include <cassert>
#include <string>

class ParsedParam {
 private:
  const int senderSocketFd;
  const std::string fullMessage;
  const std::string command;
  const std::string password;
  const std::string channelKey;
  const std::string username;
  const std::string nickname;
  const std::string channel;
  const std::string topic;
  const char modeChar;
  ParsedParam();

 public:
  ParsedParam(const int& senderSocketFd, const std::string& fullMessage,
              const std::string& command, const std::string& password,
              const std::string& channelKey, const std::string& username,
              const std::string& nickname, const std::string& channel,
              const std::string& topic, const char& modeChar);
  ParsedParam(const ParsedParam& other);
  ParsedParam& operator=(const ParsedParam& other);
  ~ParsedParam();
  const int& getSenderSocketFd();
  const std::string& getFullMessage();
  const std::string& getCommand();
  const std::string& getPassword();
  const std::string& getChannelKey();
  const std::string& getUsername();
  const std::string& getNickname();
  const std::string& getChannel();
  const std::string& getTopic();
  const char& getModeChar();
};

#endif