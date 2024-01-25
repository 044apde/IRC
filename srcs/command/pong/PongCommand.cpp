#include "PongCommand.hpp"

PongCommand::PongCommand() : ACommand() {}

PongCommand::~PongCommand() {}

PongCommand::PongCommand(const PongCommand& other) { static_cast<void>(other); }

PongCommand& PongCommand::operator=(const PongCommand& other) {
  static_cast<void>(other);
  return *this;
}

CommandResponseParam PongCommand::execute(ServerParam& serverParam,
                                          ParsedParam& parsedParam) {
  CommandResponseParam commandResponse;

  std::string daemon = parsedParam.getServerName();
  if (daemon.empty() == true) {
    commandResponse.setResponseMessage(
        this->replyMessage.errNoOrigin(parsedParam));
  }
  return commandResponse;
}