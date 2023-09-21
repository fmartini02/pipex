# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmartini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 19:12:26 by fmartini          #+#    #+#              #
#    Updated: 2023/05/28 19:47:47 by fmartini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
      free.c \
      error.c \
      childs.c \
      ft_strjoin.c \
      ft_strdup.c \
      ft_strncmp.c \
      ft_split.c \
      ft_strlen.c \

LIB_PIPEX = pipex.a

OBJS = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(LIB_PIPEX) $(OBJS)
	$(CC) $(CFLAGS) $< -o $@

$(LIB_PIPEX): $(OBJS)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I. -c  $< -o $@

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

