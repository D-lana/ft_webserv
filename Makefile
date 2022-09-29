NAME		= Server

FLAGS		= -Wall -Wextra -Werror 
#-g
# -fsanitize=address
# -std=c++98

SRCS		= main.cpp Response.cpp Request.cpp Location.cpp \
			Processor.cpp Http.cpp Parser.cpp ServerPairs.cpp ConfigTokens.cpp

HEADERS		= Core.hpp Server.hpp \
			Response.hpp Request.hpp Location.hpp \
			Processor.hpp Http.hpp Parser.hpp ServerPairs.hpp ConfigTokens.hpp

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