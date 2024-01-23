#pragma once
#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>

#include "../param/parsed_param/ParsedParam.hpp"
#include "../param/server_param/ServerParam.hpp"

class ICommand {
 public:
  virtual ~ICommand() {}
  virtual std::string execute(ServerParam& serverParam,
                              const ParsedParam& parsedParam) = 0;
};

#endif
