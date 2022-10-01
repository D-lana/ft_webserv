NAME		= webserv

FLAGS		= -Wall -Wextra -Werror -g 
#-fsanitize=address -fvisibility=hidden -fvisibility-inlines-hidden
# -std=c++98

SRCS		= main.cpp Core.cpp Server.cpp Response.cpp Request.cpp Location.cpp \
			Processor.cpp Http.cpp Parser.cpp ServerPairs.cpp ConfigTokens.cpp CGI.cpp

HEADERS		= Core.hpp Server.hpp \
			Response.hpp Request.hpp Location.hpp \
			Processor.hpp Http.hpp Parser.hpp ServerPairs.hpp ConfigTokens.hpp CGI.hpp

OBJS		=	$(SRCS:.cpp=.o)

CC			=	g++

RM				= rm -Rf
FLAGS			= -Wall -Wextra -Werror -g 
#-fsanitize=address
# -std=c++98

all:			$(NAME)

test:			$(NAME)
				@./$(NAME) configs/test.conf

$(NAME):		$(OBJS) $(HEADERS)
				$(CC) -o $(NAME) $(OBJS)

%.o: %.cpp		Makefile $(HEADERS)
				$(CC) $(FLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re