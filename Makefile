# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 15:55:24 by francema          #+#    #+#              #
#    Updated: 2025/02/28 14:31:19 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRC =main.c \
	init_struct.c \
	get_cmd_path.c \
	forking.c \
	execute_cmds.c \
	pipe_closing.c \
	mem_cleaner.c \

BONUS_SRC =main_bonus.c \
	init_struct_bonus.c \
	get_cmd_path_bonus.c \
	forking_bonus.c \
	execute_here_doc_bonus.c \
	execute_cmds_bonus.c \
	pipe_closing_bonus.c \
	mem_cleaner_bonus.c \

OBJ = $(addprefix mandatory/, $(SRC:.c=.o))

BONUS_OBJ = $(addprefix bonus/, $(BONUS_SRC:.c=.o))

NAME = pipex

NAME_BONUS = pipex_bonus

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

$(NAME_BONUS): $(BONUS_OBJ) $(LIBFT) $(GNL) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJ) $(GNL) $(LIBFT) $(PRINTF)

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	make -C ./libft clean
	make -C ./ft_printf clean
	make -C ./get_next_line clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make -C ./libft fclean
	make -C ./ft_printf fclean
	make -C ./get_next_line fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re
