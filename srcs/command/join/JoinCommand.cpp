#include "JoinCommand.hpp"

JoinCommand::JoinCommand() : ACommand() {}

JoinCommand::~JoinCommand() {}

JoinCommand::JoinCommand(const JoinCommand& other) { static_cast<void>(other); }

JoinCommand& JoinCommand::operator=(const JoinCommand& other) {
  static_cast<void>(other);
  return *this;
}

bool JoinCommand::isInValidChannelKey(const std::string& parsedChannelKey,
                                      const std::string& channelKey) const {
  if (channelKey.empty() == true || parsedChannelKey != channelKey) {
    return true;
  }
  return false;
}

bool JoinCommand::isClientChannelSizeOver(Client* client) const {
  if (client->getChannelSetSize() >= 10) {
    return true;
  }
  return false;
}

bool JoinCommand::isValidParamter(CommandResponseParam& commandResponse,
                                  const TokenParam& tokenParam,
                                  const std::string& senderNickname) {
  const std::vector<std::string>& parameter = tokenParam.getParameter();

  if (parameter.size() < 1) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errNeedMoreParams(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  if (parameter.size() > 2 || isTrailing(parameter[0]) == true ||
      (parameter.size() == 2 && isTrailing(parameter[1]) == true) ||
      isValidChannelName(parameter[0]) == false) {
    commandResponse.addResponseMessage(
        tokenParam.getSenderSocketFd(),
        this->replyMessage.errUnknownCommand(senderNickname,
                                             tokenParam.getCommand()));
    return false;
  }
  return true;
}

CommandResponseParam JoinCommand::execute(ServerParam& serverParam,
                                          const TokenParam& tokenParam) {
  CommandResponseParam commandResponse;

  const int& senderSocketFd = tokenParam.getSenderSocketFd();
  Client* client = serverParam.getClient(senderSocketFd);
  const std::string& senderNickname = client->getNickname();

  if (isValidParamter(commandResponse, tokenParam, senderNickname) == false) {
    return commandResponse;
  }

  const std::vector<std::string>& parameter = tokenParam.getParameter();
  const std::string& channelName = parameter[0];
  std::string channelKey;
  if (parameter.size() == 2 && parameter[1].empty() == false) {
    channelKey = parameter[1];
  }
  const std::string& senderUsername = client->getUsername();
  const std::string& senderHost = client->getHost();
  Channel* channel = serverParam.getChannel(channelName);

  if (isRegisteredClient(client) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd, this->replyMessage.errNotRegisterd(senderNickname));
  } else if (channel == NULL) {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.errTooManyChannels(senderNickname, channelName));
    } else {
      serverParam.addNewChannel(channelName, client);
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.successJoin(senderNickname, senderUsername,
                                         senderHost, channelName) +
              this->replyMessage.rplNamReply(senderNickname, channelName,
                                             ":@" + senderNickname));
    }
  } else if (channel->isSetKeyChannel() == true &&
             (parameter.size() < 2 ||
              isInValidChannelKey(parameter[1], channel->getChannelKey()) ==
                  true)) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errBadChannelKey(senderNickname, channelName));
  } else if (channel->isChannelFull() == true) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errChannelIsFull(senderNickname, channelName));
  } else if (channel->isClientInChannel(client) == true) {
    return commandResponse;
  } else if (channel->isInviteOnlyChannel() == true &&
             channel->isClientInvited(client) == false) {
    commandResponse.addResponseMessage(
        senderSocketFd,
        this->replyMessage.errInviteOnlyChan(senderNickname, channelName));
  } else {
    if (isClientChannelSizeOver(client) == true) {
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.errTooManyChannels(senderNickname, channelName));
    } else {
      commandResponse.addMultipleClientResponseMessage(
          channel->getAllClientFd(),
          this->replyMessage.successJoin(senderNickname, senderUsername,
                                         senderHost, channelName));
      serverParam.addClientAndChannelEachOther(client, channel);
      std::string nicknameList = ":";

      std::map<Client*, bool> channelClientMap = channel->getClientMap();
      for (std::map<Client*, bool>::iterator it = channelClientMap.begin();
           it != channelClientMap.end(); ++it) {
        nicknameList +=
            (it->second == true ? "@" : "") + it->first->getNickname() + " ";
      }
      commandResponse.addResponseMessage(
          senderSocketFd,
          this->replyMessage.successJoin(senderNickname, senderUsername,
                                         senderHost, channelName) +
              this->replyMessage.rplNamReply(senderNickname, channelName,
                                             nicknameList) +
              (channel->getTopic().empty() == true
                   ? ""
                   : this->replyMessage.rplTopic(senderNickname, channelName,
                                                 channel->getTopic())));
    }
  }
  return commandResponse;
}