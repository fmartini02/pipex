# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmartini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 17:17:54 by fmartini          #+#    #+#              #
#    Updated: 2023/05/28 16:21:53 by fmartini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main.c pipex.c pipex_utils.c string_utils.c ft_splitpath.c free.c ft_strlen ft_putstr ft_putchar ft_strdup ft_strncmp ft_substr

LIB_PIPEX = pipex.a

OBJS = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(LIB_PIPEX) $(OBJS)
	@$(CC) $(CFLAGS) -I. $< -o $@

$(LIB_PIPEX): $(OBJS)
	@ar -rcs $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re : fclean all
