NAME		= webserv

FLAGS		= -Wall -Wextra -Werror -g 
#-fsanitize=address -fvisibility=hidden -fvisibility-inlines-hidden
# -std=c++98

SRCS		= main.cpp Location.cpp ServerPairs.cpp Core.cpp Server.cpp Response.cpp Request.cpp  \
			Http.cpp Parser.cpp ConfigTokens.cpp CGI.cpp

HEADERS		= library.hpp
#  Core.hpp Location.hpp  Server.hpp \
# 			Response.hpp Request.hpp ServerPairs.hpp\
# 			Http.hpp Parser.hpp ConfigTokens.hpp CGI.hpp 

OBJS		=	$(SRCS:.cpp=.o)

FILES		= site_example/cgi-bin/date.html site_example/cgi-bin/cookies.html \
				site_example/cgi-bin/date.txt site_example/cgi-bin/cookies.txt \

CC			=	g++

RM				= rm -Rf
FLAGS			= -Wall -Wextra -Werror -g 
#-fsanitize=address
# -std=c++98

all:			$(NAME)

test:			$(NAME)
				@./$(NAME) configs/test.conf

default:		$(NAME)
				@./$(NAME)

$(NAME):		$(OBJS) $(HEADERS)
				$(CC) -o $(NAME) $(OBJS)

%.o: %.cpp		Makefile $(HEADERS)
				$(CC) $(FLAGS) -c $< -o $@

delete_file:    
				-rm -Rf $(FILES)

clean:			delete_file
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re