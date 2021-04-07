NAME = microshell

SRCS = microshell.c parser.c

FLAGS = -fsanitize=address -g -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	
fclean : clean
	rm -f $(NAME)

re: fclean all