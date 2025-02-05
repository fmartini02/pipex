# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 15:57:22 by francema          #+#    #+#              #
#    Updated: 2025/01/28 17:05:15 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = get_next_line.c \
	get_next_line_utils.c

OBJ = $(SRC:.c=.o)

NAME = gnl.a

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ../libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C ../libft

$(NAME): $(OBJ) $(LIBFT)
	ar rcs $@ $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ../libft clean

fclean: clean
	rm -f $(NAME)
	make -C ../libft fclean

re: fclean all

.PHONY: all clean fclean re
