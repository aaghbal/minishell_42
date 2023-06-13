# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 04:51:47 by zel-kach          #+#    #+#              #
#    Updated: 2023/05/26 19:01:30 by aaghbal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c cmds1.c cmds2.c cmds3.c cmds4.c arg.c parsing_2.c parsing.c token_2.c token.c utils.c signals.c doc_signal.c
OBJ = ${SRC:.c=.o}

libfta = ./libft/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -I $(shell brew --prefix readline)/include

all: libftm ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} ${libfta} -L $(shell brew --prefix readline)/lib -lreadline -o $@ 
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
