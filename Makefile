##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

NAME		= plazza

CXX		= g++

RM		= rm -f

CXXFLAGS	+= -W -Wall -Wextra -std=c++11

CPPFLAGS	+= -Iinclude/

NAME_SRCS	= $(addprefix src/, \
		main.cpp	\
		Plazza.cpp	\
		Namedpipe.cpp	\
		Thread.cpp	\
		StringFunc.cpp	\
		Slave.cpp	\
		Parser.cpp	\
		Regex.cpp)

NAME_OBJS	= $(NAME_SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(NAME_OBJS)
		$(CXX) $(NAME_OBJS) -o $(NAME) $(LDFLAGS) $(CPPFLAGS) -lpthread

clean:
		$(RM) $(NAME_OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
