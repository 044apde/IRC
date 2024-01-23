#include "ACommand.hpp"

ACommand::ACommand() : replyMessage(ReplyMessage::getInstance()) {}

ACommand::~ACommand() {}

ACommand::ACommand(const ACommand& other)
    : replyMessage(ReplyMessage::getInstance()) {
  static_cast<void>(other);
}

ACommand& ACommand::operator=(const ACommand& other) {
  static_cast<void>(other);
  return *this;
}
