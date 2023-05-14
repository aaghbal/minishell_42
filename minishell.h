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
	redirections,
	NONE
}e_type;

typedef struct s_token{
	char *cmd;
	e_type type;
	struct s_token *next;
}t_token;

typedef struct s_arg{
	char *cmd;
	char **arg;
	e_type type;
	struct s_arg *next;
}t_arg;

typedef struct s_data
{
	int		i;
	char	*str;
}t_data;

void	token_line(char *line);
char	*append_char(char *str, char c);
int		check_token(char c);
e_type	get_type(char *str);
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
char	*char_to_str(char *line);
t_token	*new_token(char *cmd, e_type type);
char	*print_token(int n);
int		get_end(char *line, int i);
char	*double_quotes(char *line,char *str, int *len);
char	*single_quotes(char *line,char *str, int *len);
void	add_free(t_data *data, t_token **token);
void	is_token(t_data *data, char *line);
void	default_cmd(t_data *data, char *line);
int		is_char(char c);
char	*get_token(char *line);
t_arg * newarg_token(char *cmd, e_type type);
void	ft_argadd_back(t_arg **lst, t_arg *new);
char **alloc_arg(char **args, char *cmd);
t_arg	*ft_arglast(t_arg *lst);
 void	free_tab(char **tab);
 void	is_arg(t_token *tmp, t_arg **arg);




#endif





