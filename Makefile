# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 15:55:24 by francema          #+#    #+#              #
#    Updated: 2025/02/13 17:17:01 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRC =main.c \
	init_struct.c \
	get_cmd_path.c \
	execute_here_doc.c \
	execute_cmds.c \
	pipe_closing.c \
	mem_cleaner.c \

OBJ = $(SRC:.c=.o)

NAME = pipex

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a

GNL = get_next_line/gnl.a

PRINTF = ft_printf/libftprintf.a

all: $(NAME)

$(LIBFT):
	make -C libft

$(GNL):
	make -C get_next_line

$(PRINTF):
	make -C ft_printf

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(GNL) $(LIBFT) $(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	make -C ./ft_printf clean
	make -C ./get_next_line clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	make -C ./ft_printf fclean
	make -C ./get_next_line fclean

re: fclean all

.PHONY: all clean fclean re
