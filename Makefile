# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 15:55:24 by francema          #+#    #+#              #
#    Updated: 2025/01/28 18:16:19 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRC =main.c \
	init_struct.c \
	get_cmd_path.c \
	execute_here_doc.c \
	execute_cmds.c \
	pipe_closing.c \

OBJ = $(SRC:.c=.o)

NAME = pipex

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a

GNL = get_next_line/gnl.a

all: $(NAME)

$(LIBFT):
	make -C libft

$(GNL):
	make -C get_next_line

$(NAME): $(OBJ) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(GNL) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	make -C ./get_next_line clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	make -C ./get_next_line fclean

re: fclean all

.PHONY: all clean fclean re
