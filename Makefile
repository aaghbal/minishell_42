# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 04:51:47 by zel-kach          #+#    #+#              #
#    Updated: 2023/05/14 04:51:48 by zel-kach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c signals.c cmds1.c cmds2.c cmds3.c cmds4.c cmds5.c arg.c parsing_2.c parsing.c token_2.c token.c
OBJ = ${SRC:.c=.o}

libfta = ./libft/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -g

all: libftm ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} ${libfta} -lreadline -o $@

%.o: %.c minishell.h ${libfta}
		${CC} ${CFLAGS} -c $<

libftm:
		make -C libft

libftclean:
			make clean -C libft

libftfclean:
			make fclean -C libft

clean: libftclean
		${RM} ${OBJ}

fclean: clean libftfclean
		${RM} ${NAME}

re: fclean all
