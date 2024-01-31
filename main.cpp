#include <iostream>

#include "srcs/server/Server.hpp"

int main(int ac, char** av) {
  Server server(ac, av);

  try {
    server.run();
  } catch (const std::exception& e) {
    std::cerr << typeid(e).name() << '\n';                 // seonghle
    std::cerr << "main exception : " << e.what() << '\n';  // seonghle
  }
  return 0;
}