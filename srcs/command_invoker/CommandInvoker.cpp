#include "CommandInvoker.hpp"

CommandInvoker::CommandInvoker() : replyMessage(ReplyMessage::getInstance()) {
  this->commandMap.insert(std::make_pair("INVITE", new InviteCommand()));
  this->commandMap.insert(std::make_pair("JOIN", new JoinCommand()));
  this->commandMap.insert(std::make_pair("KICK", new KickCommand()));
  this->commandMap.insert(std::make_pair("MODE", new ModeCommand()));
  this->commandMap.insert(std::make_pair("NICK", new NickCommand()));
  this->commandMap.insert(std::make_pair("PART", new PartCommand()));
  this->commandMap.insert(std::make_pair("PASS", new PassCommand()));
  this->commandMap.insert(std::make_pair("PING", new PingCommand()));
  this->commandMap.insert(std::make_pair("PONG", new PongCommand()));
  this->commandMap.insert(std::make_pair("PRIVMSG", new PrivmsgCommand()));
  this->commandMap.insert(std::make_pair("QUIT", new QuitCommand()));
  this->commandMap.insert(std::make_pair("TOPIC", new TopicCommand()));
  this->commandMap.insert(std::make_pair("USER", new UserCommand()));
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
                                             TokenParam& tokenParam) {
  std::map<std::string, ACommand*>::iterator it =
      this->commandMap.find(tokenParam.getCommand());
  if (it == this->commandMap.end()) {
    CommandResponseParam commandResponse;
    ParsedParam parsedParam =
        ParsedParamBuilder()
            .senderSocketFd(tokenParam.getSenderSocketFd())
            .command(tokenParam.getCommand())
            .build();

    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand(parsedParam));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return commandResponse;
  }
  return it->second->execute(serverParam, tokenParam);
}
