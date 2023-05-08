/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:49:32 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/06 10:49:34 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum type{
	TokenWord,
	tokenPipe,
	redirections
}e_type;

typedef struct s_token{
	char *cmd;
	enum type typee;
	struct s_token *next;
}t_token;


void	token_line(char *line);
char	*append_char(char *str, char c);
int		is_token(char c);
e_type	get_type(char *str);
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
char	*char_to_str(char *line);
t_token	*new_token(char *cmd, e_type type);


#endif





