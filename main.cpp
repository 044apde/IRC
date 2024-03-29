#include <iostream>

#include "srcs/server/Server.hpp"

Server server;

int main(int ac, char** av) {
  server = Server(ac, av);

  try {
    signal(SIGINT, intHandler);
    server.run();
  } catch (const std::exception& e) {
    std::cerr << typeid(e).name() << '\n';
    std::cerr << "main exception : " << e.what() << '\n';
  }
  return 0;
}