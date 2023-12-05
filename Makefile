# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 16:32:36 by glambrig          #+#    #+#              #
#    Updated: 2023/12/04 17:41:46 by glambrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = minishell

CC = gcc

LDFLAGS = -L./libft -lft

LFT = ./libft/*.o

CFLAGS = -g -Wall -Wextra #-Werror

SRC = executable.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LFT) $(OBJ)
	$(CC) $(SRC) -o $@ $(LDFLAGS) $(CFLAGS)

$(OBJ): %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(LFT):
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean

re: fclean all
