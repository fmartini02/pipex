SRC =main.c \
	init_struct.c \
	get_cmd_path.c \
	execute_here_doc.c \
	execute_cmds.c \

OBJ = $(SRC:.c=.o)

NAME = pipex

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
