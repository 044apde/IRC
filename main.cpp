#include "srcs/parse/ServerInfo.hpp"
#include "srcs/socket/ServerSocket.hpp"
#include "srcs/utils/utils.hpp"

int main(int ac, char** av) {
  ServerInfo serverInfo(ac, av);
  ServerSocket serverSocket(serverInfo);

  initSignal();
  while (true)
    ;
  return 0;
}