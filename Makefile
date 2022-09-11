NAME		= Server

FLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
# -std=c++98

SRCS		= main.cpp Response.cpp Request.cpp \
			Processor.cpp

HEADERS		= Core.hpp Server.hpp \
			Response.hpp Request.hpp \
			Processor.hpp

OBJS		= $(SRCS:.cpp=.o)

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			g++ -o $(NAME) $(OBJS)

%.o: %.cpp	Makefile $(HEADERS)
			g++ $(FLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
