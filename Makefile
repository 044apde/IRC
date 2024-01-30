TARGET = ircserv
CXX = c++
CXXFLAGS =  -std=c++98 -fsanitize=address -g
SOURCES = main.cpp \
	srcs/channel/Channel.cpp \
	srcs/client/Client.cpp \
	srcs/command/invite/InviteCommand.cpp \
	srcs/command/join/JoinCommand.cpp \
	srcs/command/kick/KickCommand.cpp \
	srcs/command/mode/ModeCommand.cpp \
	srcs/command/nick/NickCommand.cpp \
	srcs/command/part/PartCommand.cpp \
	srcs/command/pass/PassCommand.cpp \
	srcs/command/ping/PingCommand.cpp \
	srcs/command/pong/PongCommand.cpp \
	srcs/command/privmsg/PrivmsgCommand.cpp \
	srcs/command/quit/QuitCommand.cpp \
	srcs/command/topic/TopicCommand.cpp \
	srcs/command/user/UserCommand.cpp \
	srcs/command_invoker/CommandInvoker.cpp \
	srcs/param/command_response_param/CommandResponseParam.cpp \
	srcs/param/server_param/ServerParam.cpp \
	srcs/param/token_param/TokenParam.cpp \
	srcs/reply_message/ReplyMessage.cpp \
	srcs/server/Server.cpp \
	srcs/command/ACommand.cpp


OBJ = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ): %.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: 
	Make fclean 
	Make all

.PHONY: all clean fclean re