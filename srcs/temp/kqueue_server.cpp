#include <arpa/inet.h>
// #include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// change_events(eventVec, serverSocketFd, EVFILT_READ, EV_ADD, 0, 0, NULL);

void change_events(std::vector<struct kevent> &change_list, uintptr_t ident,
                   int16_t filter, uint16_t flags, uint32_t fflags,
                   intptr_t data, void *udata) {
  struct kevent temp_event;

  EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
  change_list.push_back(temp_event);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "main arg count error" << std::endl;
    return 1;
  }

  // socket 서버 열기
  int serverSocketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (serverSocketFd < 0) {
    std::cout << "socket error" << std::endl;
    return 1;
  }

  // socket 설정
  struct sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  int portNum = std::atoi(argv[1]);
  if (portNum > 65535 || portNum <= 1024) {
    std::cout << "port number error" << std::endl;
    return 1;
  }
  server_addr.sin_port = htons(portNum);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // socket 서버에 주소 설정
  if (bind(serverSocketFd, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == -1) {
    perror("Bind failed");
    std::exit(EXIT_FAILURE);
  }

  if (listen(serverSocketFd, 5) == -1) {
    perror("Listen failed");
    std::exit(EXIT_FAILURE);
  }

  std::cout << "Server is listening..." << std::endl;

  int kqueueFd = kqueue();
  if (kqueueFd == -1) {
    perror("Kqueue failed");
    std::exit(EXIT_FAILURE);
  }

  struct kevent eventArr[8];
  std::map<int, std::string> clientMap;
  std::vector<struct kevent> eventVec;
  for (int i = 0; i < 8; i++) {
    // ident - kevent호출 후 이벤트 대상 소켓 fd 입력됨
    // filter - 모니터링할 이벤트 유형
    // flags - 이벤트 제어 플래그, 이벤트 추가, 제거, 한번만 발생
    // fflags - 필터가 파일 시스템 변경 이벤트와 관련되면 파일 시스템 변경 유형
    // 지정
    // data - 이벤트와 관련된 데이터 포함, 읽기 이벤트의 경우 읽을 수 있는
    // 바이트 수
    // udata - 사용자 정의 데이터 포인터, 이벤트 발생 시마다 이 구조체에 연결된
    // 사용자 데이터 포함
    // ext - 이벤트와 관련된 사용자 지정 데이터 전달에 사용
    // EV_SET(&eventArr[i], serverSocketFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0,
    // 0,
    //        NULL);
    // eventVec.push_back(eventArr[i]);
    change_events(eventVec, serverSocketFd, EVFILT_READ, EV_ADD, 0, 0, NULL);
  }
  struct kevent *currentEvent = NULL;
  while (true) {
    int eventCount = 0;
    struct timespec timeout;

    timeout.tv_sec = 120;
    timeout.tv_nsec = 0;
    eventCount =
        kevent(kqueueFd, &eventVec[0], eventVec.size(), eventArr, 8, &timeout);
    std::cout << "event get" << std::endl;
    if (eventCount == -1) {
      perror("Kevent failed");
      std::exit(EXIT_FAILURE);
    }
    if (eventCount == 0) {
      std::cout << "Timeout(but nothing to do)" << std::endl;
      // for (std::map<int, std::string>::iterator it = clientMap.begin();
      //      it != clientMap.end(); ++it) {
      //   if (send(it->first, "PING\r\n", 0, 0) == -1) {
      //     perror("Send failed");
      //     continue;
      //   }
      // }
      continue;
    }
    eventVec.clear();
    for (int i = 0; i < eventCount; i++) {
      currentEvent = &eventArr[i];
      int eventFd = static_cast<int>(currentEvent->ident);

      if (currentEvent->flags & EV_ERROR) {
        if (eventFd == serverSocketFd)
          std::cout << "server socket error" << std::endl;
        else {
          std::cout << "client socket error" << std::endl;
          std::map<int, std::string>::iterator it = clientMap.find(eventFd);
          if (it != clientMap.end()) {
            clientMap.erase(it);
          }
        }
        std::cout << "EV_ERROR" << std::endl;
        continue;
      }

      // 이벤트 처리 루프 내
      if (currentEvent->flags & EV_EOF) {
        std::cout << "Client disconnected" << std::endl;
        close(eventFd);            // 클라이언트 소켓 닫기
        clientMap.erase(eventFd);  // 클라이언트 정보 맵에서 제거
        continue;
      }

      if (currentEvent->filter == EVFILT_READ) {
        std::cout << "EVFILT_READ" << std::endl;
        if (eventFd == serverSocketFd) {
          std::cout << "New connection" << std::endl;
          sockaddr_in clientAddr;
          socklen_t clientAddrSize = sizeof(clientAddr);
          int client_fd =
              accept(serverSocketFd, reinterpret_cast<sockaddr *>(&clientAddr),
                     &clientAddrSize);
          if (client_fd == -1) {
            perror("Accept failed");
            // std::exit(EXIT_FAILURE);
            continue;
          }
          char client_ip[INET_ADDRSTRLEN];
          inet_ntop(AF_INET, &clientAddr.sin_addr, client_ip,
                    sizeof(client_ip));
          change_events(eventVec, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0,
                        0, NULL);
          // change_events(eventVec, client_fd, EVFILT_WRITE, EV_ADD |
          // EV_ENABLE,
          //               0, 0, NULL);
          fcntl(client_fd, F_SETFL, O_NONBLOCK);
          clientMap.insert(std::pair<int, std::string>(client_fd, ""));
          std::cout << "Client connected: " << client_ip << std::endl;
          continue;
        } else if (clientMap.end() != clientMap.find(eventFd)) {
          char buffer[512];
          ssize_t n = recv(eventFd, buffer, sizeof(buffer), 0);
          std::cout << "receive data size : " << n << std::endl;

          if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
              std::cout << "recv timeout" << std::endl;
              continue;
            }
            perror("Recv failed");
            std::exit(EXIT_FAILURE);
          }
          // if (n == 0) {
          //   // TODO: 타임아웃 이후 disconnect하면 무한 루프 발생
          //   std::cout << "Client disconnected" << std::endl;
          //   if (send(eventFd, "", 0, 0) == -1) {
          //     perror("Send failed");
          //     std::exit(EXIT_FAILURE);
          //   }

          //   std::map<int, std::string>::iterator it =
          //   clientMap.find(eventFd); if (it != clientMap.end()) {
          //     clientMap.erase(it);
          //   }
          //   continue;
          // }
          if (n == 0) {
            std::cout << "Client disconnected" << std::endl;
            change_events(eventVec, eventFd, EVFILT_READ, EV_DELETE, 0, 0,
                          NULL);
            close(eventFd);            // 클라이언트 소켓 닫기
            clientMap.erase(eventFd);  // 클라이언트 정보 맵에서 제거
            continue;
          }
          buffer[n] = '\0';
          clientMap[eventFd] = buffer;
          if (n == 2 && buffer[0] == '\r' && buffer[1] == '\n') {
            std::cout << "Empty message received" << std::endl;
          } else {
            std::string text = buffer;
            text = std::regex_replace(text, std::regex("\r"), "->");
            text = std::regex_replace(
                text, std::regex("\n"),
                "\\n\n");  // 줄바꿈 문자 표현을 유지하려면 \\n을 사용합니다.

            std::cout << "Received msg from " << eventFd << ": " << text
                      << std::endl;
          }
          if (send(eventFd, clientMap[eventFd].c_str(),
                   clientMap[eventFd].size(), 0) == -1) {
            perror("Send failed");
            std::exit(EXIT_FAILURE);
          }
        } else {
          std::cout << "Client disconnected" << std::endl;
          std::map<int, std::string>::iterator it = clientMap.find(eventFd);
          if (it != clientMap.end()) {
            clientMap.erase(it);
          }
        }
        continue;
      }
      if (currentEvent->filter == EVFILT_WRITE) {
        std::cout << "EVFILT_WRITE" << std::endl;
        continue;
      }
    }
  }
  for (std::map<int, std::string>::iterator it = clientMap.begin();
       it != clientMap.end(); ++it) {
    close(it->first);
  }
  close(serverSocketFd);

  return 0;
}