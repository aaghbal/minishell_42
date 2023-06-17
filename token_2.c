/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:02 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/13 13:36:46 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_token * new_token(char *cmd, t_type type)
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


char *get_token(char *line)
{
	int i;
	
	if (!line)
		return (NULL);
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

void	ft_tokenization(t_token	**token, t_data *data, t_list *export_list, char *line)
{
	while (line[data->i])
	{
		while (line[(data->i)] == ' ' || line[(data->i)] == '\t')
			(data->i)++;
		if (check_token(line[data->i]))
			is_token(data, line);
		else if (line[data->i] == '\"')
			data->str = double_quotes(line, data->str, &(data->i), export_list);
		else if (line[data->i] == '\'')
			data->str = single_quotes(line, data->str, &(data->i));
		else
			default_cmd(data, line, export_list);
		if (data->str)
			add_free(data, token);
	}
}
int 	parsing_3(char *line)
{
	int i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i] == '\"' && line[i + 1] == '\"')
			{
				i += 2;
				c++;
				while (line[i] && (line[i] == ' ' || line[i] == '\t'))
					i++;
			}
		}
		if ((line[i] == '<' && line[i + 1] == '<' )|| (line[i] == '<' && line[i + 1] == '<'))
			c = 0;
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			c = 0;
			i++;
		}
		else
			i++;
	}
	return(c);
}

int  token_line(char *line, t_list *export_list, t_list *env_list)
{
	t_data *data;
	t_arg *arg;
	t_token	*token;

	data = malloc(sizeof(t_data));
	arg = NULL;
	token = NULL;
	data->i = 0;
	data->str = NULL;
	ft_tokenization(&token, data, export_list, line);
	if (ft_parsing_2(&token) && !parsing_3(line))
	{
		free_list(token);
		return(1);
	}
	is_arg(token, &arg);
	execute(arg, export_list, env_list);
	return(0);
}
