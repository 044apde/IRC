TARGET = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
SOURCES = main.cpp \
	srcs/parse/ServerInfo.cpp \
	srcs/socket/ServerSocket.cpp srcs/socket/ClientSocket.cpp \
	srcs/utils/signal.cpp

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