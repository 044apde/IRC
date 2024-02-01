#include "signal.hpp"

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