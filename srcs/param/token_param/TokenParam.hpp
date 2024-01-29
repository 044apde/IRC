#pragma once
#ifndef TOKEN_PARAM_HPP
#define TOKEN_PARAM_HPP

#include <string>
#include <vector>

class TokenParam {
 private:
  const int senderSocketFd;
  const std::string prefix;
  const std::string command;
  const std::vector<std::string> parameter;

 public:
  TokenParam();
  TokenParam(const int& senderSocketFd, const std::string& prefix,
             const std::string& command,
             const std::vector<std::string>& parameter);
  TokenParam(const TokenParam& other);
  TokenParam& operator=(const TokenParam& other);
  ~TokenParam();
  const int& getSenderSocketFd() const;
  const std::string& getPrefix() const;
  const std::string& getCommand() const;
  const std::vector<std::string>& getParameter() const;
};

#endif
