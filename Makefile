# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 10:49:41 by aaghbal           #+#    #+#              #
#    Updated: 2023/05/06 10:49:43 by aaghbal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
HEADER = minishell.h
NAME = minishell
SRC = minishell.c token.c
RM = rm -rf
OBJ_SRC = $(SRC:.c=.o)

all : libft $(NAME)

libft :
	make -C ./libft

$(NAME) : $(OBJ_SRC) $(HEADER)
	$(CC) $(CFLAGS) ./libft/libft.a  $(OBJ_SRC) -o $(NAME) -lreadline

%.o : %.c $(HEADER) libft.h
	$(CC) $(CFLAGS) -c $<

clean :
	make clean -C ./libft
	$(RM) $(OBJ_SRC)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all fclean clean re libft
