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

bool ModeCommand::isValidModeArgument(const std::vector<std::string> &parameter,
                                      Channel *channel) {
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
        if (signedChar == '-' && channel->isSetKeyChannel() == false) {
          continue;
        }
        argumentIndex++;
        break;
      case 'o':
        if (parameter.size() <= argumentIndex ||
            isTrailing(parameter[argumentIndex]) == true ||
            parameter[argumentIndex].empty() == true) {
          return false;
        }
        argumentIndex++;
        break;
      case 'l':
        if (signedChar == '-') {
          continue;
        }
        if (signedChar == '+' &&
            (parameter.size() <= argumentIndex ||
             isTrailing(parameter[argumentIndex]) == true ||
             parameter[argumentIndex].empty() == true)) {
          return false;
        }
        argumentIndex++;
        break;
    }
  }
  if (argumentIndex != parameter.size()) {
    return false;
  }
  return true;
}

bool ModeCommand::isValidParamter(CommandResponseParam &commandResponse,
                                  const TokenParam &tokenParam,
                                  const std::string &senderNickname) {
  const std::vector<std::string> &parameter = tokenParam.getParameter();

  if (parameter.size() < 2) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (isTrailing(parameter[0]) == true || parameter[0][0] != '#' ||
      isTrailing(parameter[1]) == true) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter[0].empty() == false && parameter[0][0] != '#') {
    return false;
  }
  if (isValidModeString(parameter[1]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownMode(senderNickname, parameter[1]));
    return false;
  }
  return true;
}

size_t getArgumentSizeIndex(const std::string &argument) {
  size_t argumentStartIndex = 0;

  for (size_t i = 0; i < argument.size(); i++) {
    if (argument[i] != '0') {
      break;
    }
    argumentStartIndex = i;
  }
  return argumentStartIndex;
}

const std::string getSize_tMaxString() {
  const size_t sizeMaxSize = std::numeric_limits<size_t>::max();
  std::ostringstream maxSizeSstream;

  maxSizeSstream << sizeMaxSize;
  return maxSizeSstream.str();
}

bool IsValidMaxUser(const std::string &argument) {
  for (size_t i = 0; i < argument.size(); i++) {
    if (isdigit(argument[i]) == false) {
      return false;
    }
  }
  size_t argumentStartIndex = getArgumentSizeIndex(argument);
  size_t argumentSize = argument.size() - argumentStartIndex;
  std::string maxSizeString = getSize_tMaxString();

  if (argumentSize > maxSizeString.size()) {
    return false;
  }
  if (argumentSize == maxSizeString.size()) {
    for (size_t i = 0; i < argumentSize; i++) {
      if (argument[i + argumentStartIndex] > maxSizeString[i]) {
        return false;
      }
    }
  }

  return true;
}

size_t ModeCommand::getMaxUserParameter(const std::string &argument) {
  std::istringstream argumentSstream(argument);
  size_t digitMaxUser;

  argumentSstream >> digitMaxUser;
  return digitMaxUser;
}

CommandResponseParam ModeCommand::execute(ServerParam &serverParam,
                                          const TokenParam &tokenParam) {
  CommandResponseParam commandResponse;
  const std::vector<std::string> &parameter = tokenParam.getParameter();
  const int &senderSocketFd = tokenParam.getSenderSocketFd();
  Client *senderClient = serverParam.getClient(senderSocketFd);
  const std::string &senderNickname = senderClient->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  const std::string &channelName = parameter[0];
  Channel *channel = serverParam.getChannel(channelName);
  if (channel == NULL || isValidModeArgument(parameter, channel) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errUnknownMode(senderNickname, parameter[1]));
    return commandResponse;
  }

  const std::string &modeString = parameter[1];
  std::vector<std::string> arguments;
  size_t argumentIndex = 2;
  const std::string &senderUsername = senderClient->getUsername();
  const std::string &senderHost = senderClient->getHost();

  if (senderClient == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (channel == NULL) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNoSuchChannel(senderNickname, channelName));
  } else if (channel->isClientInChannel(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errNotOnChannel(senderNickname, channelName));
  } else if (channel->isOpClient(senderClient) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errChaNoPrivsNeeded(senderNickname, channelName));
  } else {
    char signedChar = '\0';
    std::string keyArgument;
    std::set<std::string> opArguments;
    std::set<std::string> unsetOpArguments;
    std::vector<size_t> maxUserArguments;
    for (size_t i = 0; i < modeString.size(); i++) {
      // TODO: o에서만 쓰는 것으로 리팩토링 시 함수로 뺌
      Client *targetClient = NULL;
      if (modeString[i] == '+' || modeString[i] == '-') {
        signedChar = modeString[i];
        continue;
      }
      switch (modeString[i]) {
        case 'i':
          if (signedChar == '+') {
            channel->setInviteOnly();
          } else {
            channel->unsetInviteOnly();
          }
          break;
        case 't':
          if (signedChar == '+') {
            channel->setTopicOpOnly();
          } else {
            channel->unsetTopicOpOnly();
          }
          break;
        case 'k':
          if (signedChar == '+') {
            // channel->setKey(parameter[argumentIndex++]);
            keyArgument = parameter[argumentIndex++];
            arguments.push_back("*");
          } else {
            // channel->unsetKey();
            keyArgument.clear();  // 비어있으면 unset
          }
          break;
        case 'o':
          targetClient =
              serverParam.getClientByNickname(parameter[argumentIndex]);
          if (targetClient == NULL ||
              isRegisteredClient(targetClient) == false) {
            commandResponse.addResponseMessage(
                senderSocketFd, this->replyMessage.errNoSuchNick(
                                    senderNickname, parameter[argumentIndex]));
            return commandResponse;
          }
          if (channel->isClientInChannel(targetClient) == false) {
            commandResponse.addResponseMessage(
                senderSocketFd, this->replyMessage.errNotOnChannel(
                                    senderNickname, channelName));
            return commandResponse;
          }
          if (signedChar == '+') {
            // channel->setOpClient(targetClient);
            opArguments.insert(parameter[argumentIndex]);
          } else {
            // channel->unsetOpClient(targetClient);
            unsetOpArguments.insert(parameter[argumentIndex]);
          }
          arguments.push_back(parameter[argumentIndex++]);
          break;
        case 'l':
          if (signedChar == '+') {
            size_t digitMaxUser = getMaxUserParameter(parameter[argumentIndex]);

            if (IsValidMaxUser(parameter[argumentIndex]) == false ||
                digitMaxUser < channel->getUserCountInChannel()) {
              commandResponse.addResponseMessage(
                  senderSocketFd, this->replyMessage.errUnknownMode(
                                      senderNickname, modeString));
              return commandResponse;
            }
            // channel->setMaxUser(digitMaxUser);
            // maxUserArguments.clear();
            maxUserArguments.push_back(digitMaxUser);
            arguments.push_back(parameter[argumentIndex++]);
          } else {
            // channel->unsetMaxUser();
            maxUserArguments.push_back(0);  // 비어있으면 unset
          }
          break;
      }
    }
    if (keyArgument.empty() == false) {
      channel->setKey(keyArgument);
    } else {
      channel->unsetKey();
    }
    for (std::set<std::string>::iterator it = opArguments.begin();
         it != opArguments.end(); ++it) {
      Client *targetClient = serverParam.getClientByNickname(*it);
      channel->setOpClient(targetClient);
    }
    for (std::set<std::string>::iterator it = unsetOpArguments.begin();
         it != unsetOpArguments.end(); ++it) {
      Client *targetClient = serverParam.getClientByNickname(*it);
      channel->unsetOpClient(targetClient);
    }
    for (size_t i = 0; i < maxUserArguments.size(); i++) {
      if (maxUserArguments[i] != 0) {
        channel->setMaxUser(maxUserArguments[i]);
      } else {
        channel->unsetMaxUser();
      }
    }
    commandResponse.addMultipleClientResponseMessage(
        channel->getAllClientFd(),
        this->replyMessage.successMode(senderClient->getNickname(),
                                       senderUsername, senderHost, channelName,
                                       modeString, arguments));
  }
  return commandResponse;
}
