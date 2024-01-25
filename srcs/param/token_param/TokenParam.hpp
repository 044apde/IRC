#pragma once
#ifndef TOKEN_PARAM_HPP
#define TOKEN_PARAM_HPP

#include <string>
#include <vector>

class TokenParam {
 private:
  const std::string prefix;
  const std::string command;
  const std::vector<std::string> parameter;
  TokenParam();

 public:
  TokenParam(const std::string& prefix, const std::string& command,
             const std::vector<std::string>& parameter);
  TokenParam(const TokenParam& other);
  TokenParam& operator=(const TokenParam& other);
  ~TokenParam();
  const std::string& getPrefix() const;
  const std::string& getCommand() const;
  const std::vector<std::string>& getParameter() const;
};

#endif
