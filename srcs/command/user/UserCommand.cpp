#include "UserCommand.hpp"

UserCommand::UserCommand() : ACommand() {}

UserCommand::~UserCommand() {}

UserCommand::UserCommand(const UserCommand& other) { static_cast<void>(other); }

UserCommand& UserCommand::operator=(const UserCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool UserCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam) {
  const std::vector<std::string> parameter = tokenParam.getParameter();

  if (parameter.size() < 4) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 4 || isTrailing(parameter[0]) == true ||
      isTrailing(parameter[1]) == true || isTrailing(parameter[2]) == true ||
      isTrailing(parameter[3]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam UserCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  int senderSocketFd = tokenParam.getSenderSocketFd();
  const std::vector<std::string> parameter = tokenParam.getParameter();
  const std::string& username = parameter[0];
  Client* senderClient = serverParam.getClient(senderSocketFd);

  if (senderClient->getNickname().empty() == true) {
    commandResponse.addResponseMessage(senderSocketFd,
                                       this->replyMessage.errNotRegisterd());
  } else if (senderClient->getUsername().empty() == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errAlreadyRegistered(""));
  } else {
    senderClient->setUsername(username);
    const std::string& senderNickname = senderClient->getNickname();
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.rplWelcome(senderNickname) +
                            this->replyMessage.rplYourHost(senderNickname) +
                            this->replyMessage.rplCreated(senderNickname) +
                            this->replyMessage.rplMyInfo(senderNickname));
  }
  return commandResponse;
}
