NAME = microshell

SRCS = microshell.c parser.c

FLAGS = -fsanitize=address -g -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)
	rm -rf $(NAME).dSYM

clean :

fclean : clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME) "/bin/ls" "-l"
	@echo
	./$(NAME) "/bin/ls" "-l" "|" "/usr/bin/base64"
	@echo
	./$(NAME) "/bin/ls" "-l" "|" "/usr/bin/base64" "|" "/usr/bin/base64" "-D"
	@echo
	./$(NAME) "/bin/ls" "-l" "|" "/usr/bin/base64" "|" "/usr/bin/base64" "-D" "|" "/usr/bin/wc" "-l"
