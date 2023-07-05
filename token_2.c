/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:02 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/05 19:47:32 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(char *line)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	if (line[i] && (line[i] == '|' || line[i] == '<' || line[i] == '>')
		&& (line[i + 1] != '<' && line[i + 1] != '>'))
		return (ft_substr(line, 0, 1));
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')))
		return (ft_substr(line, 0, 2));
	return (NULL);
}

void	tokenization(t_token **tok, t_data *data, t_list *exp_list, char *line)
{
	int	c;

	c = 0;
	while (line[data->i])
	{
		c = data->i;
		while (line[(data->i)] == ' ' || line[(data->i)] == '\t')
			(data->i)++;
		if (check_token(line[data->i]))
			is_token(data, line);
		else if (line[data->i] == '\"')
			data->str = double_quotes(line, data->str, &(data->i), exp_list);
		else if (line[data->i] == '\'')
			data->str = single_quotes(line, data->str, &(data->i));
		else
			default_cmd(data, line, exp_list);
		if (data->str)
			add_free(data, tok, line, &c);
	}
}

void	ft_pars_nor(char *line, int *i, int *c)
{
	if (((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '<'
				&& line[*i + 1] == '<')))
		*c = 0;
	else if ((line[*i] == '<' || line[*i] == '>' || line[*i] == '|'))
	{
		*c = 0;
		(*i)++;
	}
	else
		(*i)++;
}

int	parsing_3(char *line)
{
	int	i;
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
			if ((line[i] == '\"' && line[i + 1] == '\"') || (line[i] == '\''
					&& line[i + 1] == '\''))
			{
				i += 2;
				c++;
				while (line[i] && (line[i] == ' ' || line[i] == '\t'))
					i++;
			}
		}
		ft_pars_nor(line, &i, &c);
	}
	return (c);
}

int	token_line(char *line, t_list *export_list, t_list *env_list)
{
	t_data	*data;
	t_arg	*arg;
	t_token	*token;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(0);
	arg = NULL;
	token = NULL;
	data->i = 0;
	data->str = NULL;
	tokenization(&token, data, export_list, line);
	if (ft_parsing_2(&token) && !parsing_3(line))
		return (free(line), free(data), free_list(token), 1);
	is_arg(token, &arg);
	free(line);
	free(data);
	free_list(token);
	execute(arg, export_list, env_list);
	free_arg(arg);
	return (0);
}
