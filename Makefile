# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 22:46:08 by marvin            #+#    #+#              #
#    Updated: 2022/08/29 22:46:08 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		=	main.cpp Parser.cpp Processor.cpp Request.cpp \
				Response.cpp Server.cpp ServerPairs.cpp 
INC			=	Parser.hpp Core.hpp Processor.hpp \
				Request.hpp Response.hpp Server.hpp \
				ServerPairs.hpp 

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	webserv

CC			=	g++

RM				= rm -Rf
FLAGS			= -Wall -Wextra -Werror -std=c++98

all:			$(NAME)

$(NAME):		$(OBJS) $(INC)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS)
 
clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re