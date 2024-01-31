#include "Server.hpp"

Server::Server() : serverParam(ServerParam()) { return; }

void Server::sendCommand(int targetFd) {
  std::vector<std::string> replyMessages;
  Client* client;

  std::cout << "[manage reply]\n";
  client = serverParam.getClient(targetFd);
  replyMessages = client->popReplyMessages();
  for (size_t i = 0; i < replyMessages.size(); i++) {
    if (send(targetFd, replyMessages[i].c_str(), replyMessages[i].size(), 0) ==
        -1)
      client->pushReplyMessages(replyMessages[i]);
    else
      std::cout << replyMessages[i];
  }
  return;
}

Server::Server(const Server& obj) {
  static_cast<void>(obj);
  return;
}

Server& Server::operator=(const Server& obj) {
  static_cast<void>(obj);
  return *this;
}

int Server::parseServerPort(char* portNum) {
  std::istringstream iss(portNum);
  unsigned long temp;

  if ((iss >> temp) == false)
    throw std::runtime_error("포트를 변환하는떼 실패했습니다.");
  if (temp < MINPORT || temp > MAXPORT)
    throw std::runtime_error("유효한 포트 범위는 49152 ~ 65535입니다.");
  return static_cast<int>(temp);
}

std::string Server::parseServerPwd(char* pwdNum) {
  size_t pwdNumLen = strlen(pwdNum);
  if (pwdNumLen != PWD_LEN)
    throw std::runtime_error("비밀번호를 4자리로 설정하세요.");
  for (size_t i = 0; i < pwdNumLen; ++i) {
    if (std::isdigit(pwdNum[i]) == 0) {
      throw std::runtime_error("비밀번호는 숫자로만 구성되어야 합니다.");
    }
  }
  return pwdNum;
}

int Server::makeServerListening(int serverPort) {
  int serverSocket;
  struct sockaddr_in serverAddr;

  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(serverPort);

  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
      -1)
    throw std::runtime_error("서버 소캣 바인딩에 실패했습니다.");
  if (listen(serverSocket, PENDING_QUEUE_SIZE))
    throw std::runtime_error("서버 리슨에 실패했습니다.");
  std::cout << "Server listen port: " << serverPort << "\n";
  return serverSocket;
}

Server::Server(int ac, char** av) {
  try {
    if (ac != 3) throw std::runtime_error("포트와 비밀번호가 필요합니다.");

    int serverPort = parseServerPort(av[1]);
    std::string serverPassword = parseServerPwd(av[2]);
    int serverFd = makeServerListening(serverPort);
    serverParam.setServerFd(serverFd);
    serverParam.setServerPassword(serverPassword);
  } catch (const std::exception& e) {
    std::cerr << "Server start exception : " << e.what() << '\n';  // seonghle
    exit(1);
  }
  return;
}

Server::~Server() {
  std::cout << "서버가 종료되었습니다." << std::endl;
  return;
}

void Server::enrollEventToVec(std::vector<struct kevent>& eventVec,
                              uintptr_t ident, int16_t filter, uint16_t flags,
                              uint32_t fflags, intptr_t data, void* udata) {
  struct kevent tempEvent;

  EV_SET(&tempEvent, ident, filter, flags, fflags, data, udata);
  eventVec.push_back(tempEvent);
  std::cout << "Enroll socket to event vector: " << ident << "\n";
  return;
}

int Server::makeKqueueFd() {
  int kqueueFd = kqueue();

  if (kqueueFd == -1)
    throw std::runtime_error("kqueue 함수 호출에 실패했습니다.");
  return kqueueFd;
}

struct timespec Server::makeTimeout() {
  struct timespec timeout;

  timeout.tv_sec = SEVER_WAIT_TIME;
  timeout.tv_nsec = 0;
  return timeout;
}

void Server::acceptClient(std::vector<struct kevent>& eventVec) {
  int clientSocket;
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  // int flag;

  if ((clientSocket = accept(serverParam.getServerFd(),
                             (struct sockaddr*)&clientAddr, &clientAddrLen)) ==
      -1)
    throw std::runtime_error("faild to accpet client");
  fcntl(clientSocket, F_SETFL, O_NONBLOCK);  // seonghle
  std::cout << "Accept client: " << clientSocket << "\n";
  serverParam.addNewClient(clientSocket);
  enrollEventToVec(eventVec, clientSocket, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0,
                   NULL);
  return;
}

std::string Server::getMessage(int clientSocket) {
  char buffer[MESSAGE_MAX_LENGTH];
  ssize_t bytesRead;
  std::string receivedMessage = "";

  while (true) {
    bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead > 0) {
      std::string temp(buffer, bytesRead);
      receivedMessage += temp;
    } else if (bytesRead < 0) {
      if (errno == EAGAIN)
        break;
      else
        throw std::runtime_error("failed to read message form client");
    } else
      return "";
  }
  return receivedMessage;
}

void Server::disconnectClient(int clientSocket,
                              std::vector<struct kevent>& eventvec) {
  struct kevent temp;
  EV_SET(&temp, clientSocket, EVFILT_READ | EVFILT_WRITE, EV_DELETE, 0, 0,
         NULL);
  std::cout << "disconnect '" << clientSocket << "\n";
  eventvec.push_back(temp);
  //  serverParam.getClient(clientSocket)->pushReplyMessages(""); OR
  //  close(socket);
  close(clientSocket);
  return;
}

std::string Server::makePrefix(std::string& clientMessage) {
  std::string prefix = "";
  size_t i = 0;

  if (clientMessage[0] != ':') {
    prefix = "";
  } else {
    while (i != clientMessage.size()) {
      prefix += clientMessage[i];
      ++i;
      if (clientMessage[i - 1] == ' ' && clientMessage[i] != ' ') break;
    }
    clientMessage = clientMessage.substr(i, clientMessage.length() - i);
  }
  return prefix;
}

std::string Server::makeCommand(std::string& clientMessage) {
  std::string command = "";
  size_t i = 0;
  while (i != clientMessage.size()) {
    if (clientMessage[i] == ' ') break;
    command += clientMessage[i];
    ++i;
  }
  clientMessage = clientMessage.substr(i, clientMessage.length() - i);
  return command;
}

std::vector<std::string> Server::makeParams(std::string clientMessage) {
  std::vector<std::string> params;
  std::string temp;
  int countSpace = 0;
  size_t i = -1;

  if (clientMessage.size() == 0 || clientMessage[0] != ' ')
    throw std::runtime_error("클라이언트 메세지가 형식에 맞지 않습니다.");
  while (++i <= clientMessage.size() - 1) {
    if (clientMessage[i] == ' ' && ++countSpace) {
      continue;
    } else if (clientMessage[i] == ':') {
      if (countSpace == 0)
        throw std::runtime_error("클라이언트 메세지가 형식에 맞지 않습니다.");
      temp = "";
      while (i <= clientMessage.size() - 1) temp += clientMessage[i++];
      params.push_back(temp);
      return params;
    } else {
      if (countSpace == 0)
        throw std::runtime_error("클라이언트 메세지가 형식에 맞지 않습니다.");
      temp = "";
      while (i <= clientMessage.size() - 1) {
        if (clientMessage[i] == ' ') break;
        temp += clientMessage[i++];
      }
      params.push_back(temp);
    }
  }
  return params;
}

std::string Server::makeCombinedBuffer(std::string clientMessage,
                                       int targetFD) {
  Client* client = serverParam.getClient(targetFD);
  std::string combinedBuffer;
  std::string remainRequestBuffer;

  if (client == NULL) throw std::runtime_error("failed to load client");
  remainRequestBuffer = client->popRemainRequestBuffer();
  combinedBuffer = remainRequestBuffer + clientMessage;
  return combinedBuffer;
}

void Server::setClientReplyMessage(CommandResponseParam cmdResParam,
                                   std::vector<struct kevent>& eventvec,
                                   int clientSocket) {
  std::map<const int, const std::string>::const_iterator iter;

  iter = cmdResParam.getClientResponseMessageMap().begin();
  for (; iter != cmdResParam.getClientResponseMessageMap().end(); iter++) {
    if (iter->first == -1) {
      disconnectClient(clientSocket, eventvec);
      continue;
    } else {
      Client* client = serverParam.getClient(iter->first);
      client->pushReplyMessages(iter->second);
      enrollEventToVec(eventvec, iter->first, EVFILT_WRITE, EV_ADD | EV_ONESHOT,
                       0, 0, NULL);
    }
  }
  return;
}

void Server::handleCombindBuffer(std::string combinedBuffer, int clientSocket,
                                 std::vector<struct kevent>& eventvec) {
  size_t i = 0;
  Client* client = serverParam.getClient(clientSocket);
  std::string completeMessage;
  std::string prefix;
  std::string command;
  std::vector<std::string> params;
  CommandResponseParam cmdresparam;

  if (client == NULL)
    throw std::runtime_error("클라이언트를 불러오는데 실패했습니다.");
  while (i <= combinedBuffer.size() - 1) {
    if (combinedBuffer[i] == '\n' && combinedBuffer[i - 1] == '\r') {
      try {
        completeMessage = combinedBuffer.substr(0, i - 1);
        combinedBuffer = combinedBuffer.substr(i + 1);
        prefix = makePrefix(completeMessage);
        command = makeCommand(completeMessage);
        params = makeParams(completeMessage);
        cmdresparam = commandInvoker.execute(
            serverParam, TokenParam(clientSocket, prefix, command, params));
        setClientReplyMessage(cmdresparam, eventvec, clientSocket);
        if (combinedBuffer.empty() == true) break;
      } catch (std::exception& e) {
        ;
      }
      i = 0;
    } else {
      ++i;
    }
  }
  return;
}

void Server::manageRequest(int targetFd, std::vector<struct kevent>& eventvec) {
  std::string combinedBuffer;

  std::cout << "[manage request]\n";
  std::string clientMessage = getMessage(targetFd);
  if (clientMessage.empty() == true) {
    disconnectClient(targetFd, eventvec);
    return;
  }
  combinedBuffer = makeCombinedBuffer(clientMessage, targetFd);
  handleCombindBuffer(combinedBuffer, targetFd, eventvec);
  return;
}

void Server::handleEvent(struct kevent* eventlist, int eventCount,
                         std::vector<struct kevent>& eventVec) {
  int targetFd;

  for (int i = 0; i < eventCount; i++) {
    targetFd = eventlist[i].ident;
    std::cout << "target fd : " << targetFd << "\n";
    if (eventlist[i].flags & EV_ERROR) continue;
    if (targetFd == serverParam.getServerFd()) {
      acceptClient(eventVec);
    } else {
      if (eventlist[i].filter == EVFILT_WRITE) sendCommand(targetFd);

      if (eventlist[i].filter == EVFILT_READ) manageRequest(targetFd, eventVec);
    }
  }
  return;
}

void Server::run() {
  int eventCount = 0;
  int kqueueFd = makeKqueueFd();
  std::vector<struct kevent> eventVec;
  struct kevent eventlist[EVENTLIST_SIZE];

  enrollEventToVec(eventVec, serverParam.getServerFd(), EVFILT_READ, EV_ADD, 0,
                   0, NULL);
  while (true) {
    std::cout << "\n-- waiting..\n";
    eventCount = kevent(kqueueFd, eventVec.data(), eventVec.size(), eventlist,
                        EVENTLIST_SIZE, NULL);
    if (eventCount == 0) {
      std::cout << "server timeout\n";
      break;
    } else if (eventCount == -1) {
      throw std::runtime_error("error kevent()");
    } else {
      eventVec.clear();
      handleEvent(eventlist, eventCount, eventVec);
    }
  }
  close(kqueueFd);
  return;
}