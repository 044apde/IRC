#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "../server/Server.hpp"

class Server;

extern Server server;

void intHandler(int sig);

#endif