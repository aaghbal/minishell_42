/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:02 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/09 13:10:04 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *print_token(int n)
{
	if (n == 0)
		return ("Word");
	else if (n == 1) 
		return ("Pipe");
	else
		return ("redirection");
}

t_token * new_token(char *cmd, e_type type)
{
	t_token * node;

	if (type == NONE)
		return (NULL);
	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	node->type = type;
	node->next = NULL;
	return (node);
}


int is_char(char c)
{
	if (c == ' ' || c == '\t' || check_token(c))
		return (1);
	return(0);
}

char *get_token(char *line)
{
	int i;

	i = 0;
	if (line[i] && (line[i] == '|' || line[i] == '<' || line[i] == '>') 
		&& (line[i + 1] != '<' && line[i + 1] != '>'))
		return ft_substr(line, 0, 1);
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<')
	|| (line[i] == '>' && line[i + 1] == '>')))
		return ft_substr(line, 0, 2);
	return NULL;

}

void	is_token(t_data *data, char *line)
{
	data->str = get_token(&line[(data->i)++]);
		if (ft_strlen(data->str) == 2)
			(data->i)++;
}

void token_line(char *line)
{
	t_data *data;
	t_arg *arg;
	t_token	*token;

	data = malloc(sizeof(t_data));
	arg = NULL;
	token = NULL;
	data->i = 0;
	data->str = NULL;
	while (line[data->i])
	{
		while (line[(data->i)] == ' ' || line[(data->i)] == '\t')
			(data->i)++;
		if (check_token(line[data->i]))
			is_token(data, line);
		else if (line[data->i] == '\"')
			data->str = double_quotes(line, data->str, &(data->i));
		else if (line[data->i] == '\'')
			data->str = single_quotes(line, data->str, &(data->i));
		else
			default_cmd(data, line);
		if (data->str)
			add_free(data, &token);
	}
	is_arg(token, &arg);
	for(t_arg *t = arg;t; )
	{
		printf("cmd = %s\n", t->cmd);
		for (int i = 0; t->arg[i];i++)
			printf("args[%d] = %s\n",i, t->arg[i]);
		t = t->next;
		printf("-----------------\n");
	}
	printf("yes\n");
}

