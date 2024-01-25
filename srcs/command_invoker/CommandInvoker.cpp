#include "CommandInvoker.hpp"

CommandInvoker::CommandInvoker() : replyMessage(ReplyMessage::getInstance()) {
  this->commandMap.insert(std::make_pair("PASS", new PassCommand()));
  this->commandMap.insert(std::make_pair("NICK", new NickCommand()));
  this->commandMap.insert(std::make_pair("USER", new UserCommand()));
  this->commandMap.insert(std::make_pair("JOIN", new JoinCommand()));
  this->commandMap.insert(std::make_pair("INVITE", new InviteCommand()));
  return;
}

CommandInvoker::~CommandInvoker() {
  for (std::map<std::string, ACommand*>::iterator it = this->commandMap.begin();
       it != this->commandMap.end(); it++) {
    delete it->second;
  }
  return;
}

CommandResponseParam CommandInvoker::execute(ServerParam& serverParam,
                                             ParsedParam& parsedParam) {
  std::map<std::string, ACommand*>::iterator it =
      this->commandMap.find(parsedParam.getCommand());
  if (it == this->commandMap.end()) {
    CommandResponseParam commandResponse;
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand(parsedParam));
    return commandResponse;
  }
  return it->second->execute(serverParam, parsedParam);
}
