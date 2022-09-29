NAME		= MutantStack

FLAGS		= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp 

OBJS		= $(SRCS:.cpp=.o)

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			g++ -o $(NAME) $(OBJS)

%.o: %.cpp	Makefile MutantStack.hpp
			g++ $(FLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re