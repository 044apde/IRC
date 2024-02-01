#include <iostream>

#include "srcs/server/Server.hpp"

Server server;

void intHandler(int sig) {
  for (std::map<int, Client*>::iterator it =
           server.getServerParam().getClientMap().begin();
       it != server.getServerParam().getClientMap().end(); it++) {
    close(it->first);
    std::cout << "close " << it->first << "\n";
  }
  (void)sig;
  exit(0);
  return;
}

int main(int ac, char** av) {
  server = Server(ac, av);

  try {
    signal(SIGINT, intHandler);
    server.run();
  } catch (const std::exception& e) {
    std::cerr << typeid(e).name() << '\n';                 // seonghle
    std::cerr << "main exception : " << e.what() << '\n';  // seonghle
  }
  return 0;
}