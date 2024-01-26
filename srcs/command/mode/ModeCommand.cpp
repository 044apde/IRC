#include "ModeCommand.hpp"

ModeCommand::ModeCommand() : ACommand() {}

ModeCommand::~ModeCommand() {}

ModeCommand::ModeCommand(const ModeCommand &other) { static_cast<void>(other); }

ModeCommand &ModeCommand::operator=(const ModeCommand &other) {
  static_cast<void>(other);
  return *this;
}

bool ModeCommand::isValidSignedChar(const std::string &modeString,
                                    const size_t &index) {
  assert(index != 0);
  const char &currentChar = modeString[index];

  if (currentChar != '+' && currentChar != '-') {
    return false;
  }
  const char &prevChar = modeString[index - 1];

  if (prevChar == '+' || prevChar == '-') {
    return false;
  }
  return true;
}

bool ModeCommand::isValidMode(const char &modeChar) {
  if (modeChar != 'i' && modeChar != 't' && modeChar != 'k' &&
      modeChar != 'o' && modeChar != 'l') {
    return false;
  }
  return true;
}

// 모드가 아닌 문자면서 부호가 아니거나, 부호 앞에 또 부호가 있으면 false
bool ModeCommand::isValidModeString(const std::string &modeString) {
  if (modeString.size() == 0 || modeString.size() == 1) {
    return false;
  }
  if (modeString[0] != '+' && modeString[0] != '-') {
    return false;
  }
  for (size_t i = 1; i < modeString.size(); i++) {
    if (isValidMode(modeString[i]) == false &&
        isValidSignedChar(modeString, i) == false) {
      return false;
    }
  }
  return true;
}

bool ModeCommand::isValidModeArgument(
    const std::vector<std::string> &parameter) {
  const std::string &modeString = parameter[1];
  char signedChar = modeString[0];
  size_t argumentIndex = 2;

  for (size_t i = 1; i < modeString.size(); i++) {
    if (modeString[i] == '+' || modeString[i] == '-') {
      signedChar = modeString[i];
      continue;
    }
    switch (modeString[i]) {
      case 'k':
        if (signedChar == '+' &&
            (parameter.size() <= argumentIndex ||
             isTrailing(parameter[argumentIndex]) == true ||
             parameter[argumentIndex].empty() == true)) {
          return false;
        }
        argumentIndex++;
        break;
      case 'o':
        if (parameter.size() <= argumentIndex ||
            isTrailing(parameter[argumentIndex]) == true ||
            parameter[argumentIndex].empty() == true) {
          return false;
        }
        break;
      case 'l':
        if (signedChar == '+' &&
            (parameter.size() <= argumentIndex ||
             isTrailing(parameter[argumentIndex]) == true ||
             parameter[argumentIndex].empty() == true)) {
          return false;
        }
        break;
    }
  }
  if (argumentIndex != parameter.size()) {
    return false;
  }
  return true;
}

bool ModeCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam) {
  const std::vector<std::string> &parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNeedMoreParams("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (isTrailing(parameter[0]) == true || isTrailing(parameter[1]) == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownCommand("", tokenParam.getCommand()));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  if (isValidModeString(parameter[1]) == false ||
      isValidModeArgument(parameter) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errUnknownMode("", parameter[1]));
    commandResponse.addTargetClientFd(tokenParam.getSenderSocketFd());
    return false;
  }
  return true;
}

bool IsDigitMaxUser(const std::string &argument) {
  for (size_t i = 0; i < argument.size(); i++) {
    if (isdigit(argument[i]) == false) {
      return false;
    }
  }
  return true;
}

size_t getDigitMaxUser(const std::string &argument) {
  size_t digitMaxUser = 0;

  for (size_t i = 0; i < argument.size(); i++) {
    digitMaxUser *= 10;
    digitMaxUser += argument[i] - '0';
  }
  return digitMaxUser;
}

// 모드에서 필요한 것은 다시 파싱할 때 받아오므로 그 때 다시 구현
CommandResponseParam ModeCommand::execute(ServerParam &serverParam,
                                          const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;

  if (isValidParamter(commandResponse, tokenParam) == false) {
    return commandResponse;
  }

  const int &senderSocketFd = tokenParam.getSenderSocketFd();
  const std::vector<std::string> &parameter = tokenParam.getParameter();
  const std::string &channelName = parameter[0];
  const std::string &modeString = parameter[1];
  std::vector<std::string> arguments;
  size_t argumentIndex = 2;
  Client *senderClient = serverParam.getClient(senderSocketFd);
  Channel *channel = serverParam.getChannel(channelName);

  if (senderClient == NULL) {
    commandResponse.setResponseMessage(this->replyMessage.errNotRegisterd());
  } else if (channel == NULL) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoSuchChannel("", channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNotOnChannel("", channelName));
  } else if (channel->isOpClient(senderClient) == false) {
    commandResponse.setResponseMessage(
        this->replyMessage.errChaNoPrivsNeeded("", channelName));
  } else {
    for (size_t i = 0; i < modeString.size(); i++) {
      if (modeString[i] == '+' || modeString[i] == '-') {
        continue;
      }
      switch (modeString[i]) {
        case 'i':
          if (modeString[i] == '+') {
            channel->setInviteOnly();
          } else {
            channel->unsetInviteOnly();
          }
          break;
        case 't':
          if (modeString[i] == '+') {
            channel->setTopicOpOnly();
          } else {
            channel->unsetTopicOpOnly();
          }
          break;
        case 'k':
          if (modeString[i] == '+') {
            channel->setKey(parameter[argumentIndex++]);
            arguments.push_back("*");
          } else {
            channel->unsetKey();
          }
          break;
        case 'o':
          Client *targetClient =
              serverParam.getClientByNickname(parameter[argumentIndex]);

          if (targetClient == NULL) {
            commandResponse.setResponseMessage(
                this->replyMessage.errNoSuchNick("", parameter[argumentIndex]));
            commandResponse.addTargetClientFd(senderSocketFd);
            return commandResponse;
          }
          if (channel->isClientInChannel(targetClient) == false) {
            commandResponse.setResponseMessage(
                this->replyMessage.errNotOnChannel("", channelName));
            commandResponse.addTargetClientFd(senderSocketFd);
            return commandResponse;
          }
          if (modeString[i] == '+') {
            channel->setOpClient(targetClient);
          } else {
            channel->unsetOpClient(targetClient);
          }
          arguments.push_back(parameter[argumentIndex++]);
          break;
        case 'l':
          if (modeString[i] == '+') {
            size_t digitMaxUser = getDigitMaxUser(parameter[argumentIndex]);

            if (IsDigitMaxUser(parameter[argumentIndex]) == false ||
                digitMaxUser < channel->getUserCountInChannel()) {
              commandResponse.setResponseMessage(
                  this->replyMessage.errUnknownMode("", modeString));
              commandResponse.addTargetClientFd(senderSocketFd);
              return commandResponse;
            }
            channel->setMaxUser(digitMaxUser);
            arguments.push_back(parameter[argumentIndex++]);
          } else {
            channel->unsetMaxUser();
          }
          break;
      }
    }
    commandResponse.setResponseMessage(
        this->replyMessage.successMode(modeString, arguments));
    channel->setAllClientFd(commandResponse.getTargetClientFdSet());
  }
  if (commandResponse.getTargetClientFdSet().empty() == true) {
    commandResponse.addTargetClientFd(senderSocketFd);
  }
  return commandResponse;
}