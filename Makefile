NAME		= minishell

SRC			= main.c ft_export.c ft_env.c ft_unset.c ft_parser.c \
			ft_echo.c ft_cd.c ft_pwd.c ft_exit.c
SRCS		= $(addprefix srcs/, $(SRC))

OBJS		= $(SRCS:.c=.o)

CC			= gcc

INC			= -I ./ -I ./libft

FLAGS		= -Wall -Wextra -Werror -fsanitize=address  -g
#

READLFLAG	= -L/Users/esobchak/.brew/Cellar/readline/8.1/lib/ \
			-I/Users/esobchak/.brew/Cellar/readline/8.1/include \
			-lreadline
LIBFT		= -L libft -lft

all:$(NAME)

$(NAME):
	@make -C ./libft
	@$(CC) ${FLAGS} ${READLFLAG} ${SRCS} ${LIBFT} -o ${NAME}
	@echo "\033[0;33m\t>>>>>Compile minishell done!<<<<"

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft
	@echo "\033[0;33m>>>Clean .o files done!<<<"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft
	@echo "\033[0;33m>>>Clean all files done!<<<"

re: fclean all

# norm :
# 	norminette *.h ./libft/*.c ./libft/*.h ./srcs/*.c

.PHONY: all clean fclean re norm
