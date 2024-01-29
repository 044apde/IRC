TARGET = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
SOURCES = main.cpp \
	srcs/channel/*.cpp \
	srcs/client/*.cpp \
	srcs/command/*/*.cpp \
	srcs/command/*.cpp \
	srcs/command_invoker/*.cpp \
	srcs/param/*/*.cpp \
	srcs/reply_message/*.cpp \
	srcs/server/*.cpp


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