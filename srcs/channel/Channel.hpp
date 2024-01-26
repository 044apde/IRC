#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <set>
#include <string>

#include "../client/Client.hpp"

class Client;

class Channel {
 private:
  bool isInviteOnly;
  bool isSetTopicOpOnly;
  bool isSetKey;
  bool isSetMaxUSer;
  size_t maxUser;
  std::string key;
  std::string topic;
  std::map<Client*, bool> clientMap;
  std::set<Client*> invitedclientSet;
  Channel();

 public:
  Channel(const std::string& channelName);
  ~Channel();
  Channel(const Channel& other);
  Channel& operator=(const Channel& other);
  void messageBroadcast(std::string message);
  void inviteClient(Client* invitedClient);
  void setInviteOnly();
  void setTopicOpOnly();
  void setKey(std::string key);
  void setMaxUser(size_t maxUser);
  void setOpClient(Client* client);
  void setTopic(const std::string& topic);
  void unsetInviteOnly();
  void unsetTopicOpOnly();
  void unsetKey();
  void unsetMaxUser();
  void unsetOpClient(Client* client);
  bool isInviteOnlyChannel();
  bool isSetTopicOpOnlyChannel();
  bool isSetKeyChannel();
  bool isKeyMatched(std::string key);
  // isSetMaxUser가 true일 때만 채널 최대 인원 수 확인, 아니면 무조건 false 반환
  bool isChannelFull();
  bool isClientInChannel(Client* client);
  bool isClientInChannelByNickname(std::string nickname);
  bool isOpClient(Client* client);
  bool isClientInvited(Client* client);
  // 처음 추가되는 클라이언트일 시 op 권한 부여를 위해 값을 true로 넣음
  // 초대 목록에 있는 클라이언트일 시 초대 목록에서 제거
  void addClient(Client* client);
  // 채널 목록과 초대 목록에서 모두 삭제
  void removeClient(Client* client);
  const std::string& getChannelKey() const;
  const std::string& getTopic() const;
  void setAllClientFd(std::set<int>& clientFdSet);
};

#endif