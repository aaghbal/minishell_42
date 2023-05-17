/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:00 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/09 18:33:03 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	get_next_quotes(char *line, int n, int i)
{
	char c;
	
	c = '\"';
	if (n == 1)
		c = '\'';
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return(0);
}

char	*double_quotes(char *line,char *str, int *len)
{
	int on;

	on = 1;
	++(*len);
	if (line[(*len)] != '\"')
		str = append_char(str, line[(*len)++]);
	while (line[(*len)])
	{
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\'' && line[(*len) - 1] == '\"' 
		&& get_next_quotes(line, 0, *len) == 0)
		{
			str = single_quotes(line, str, len);
		}
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\"')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
		(*len)++;
	}
	return (str);
}

char	*single_quotes(char *line,char *str, int *len)
{
	int on;

	on = 1;
	++(*len);
	if (line[(*len)] != '\'')
		str = append_char(str, line[(*len)++]);
	while (line[(*len)])
	{
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\"' && line[(*len) - 1] == '\''
		&& get_next_quotes(line, 1, *len) == 0)
			str = double_quotes(line, str, len);
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\'')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
		(*len)++;
	}
	return (str);
}

void	default_cmd(t_data *data, char *line)
{
	while (line[(data->i)] && !is_char(line[data->i]))
	{
		if (line[(data->i)] != '\"' && line[data->i] != '\'')
			data->str = append_char(data->str, line[(data->i)++]);
		else
		{

			if (line[(data->i)] == '\"')
				data->str = double_quotes(line, data->str, &(data->i));
			else if (line[data->i] == '\'')
				data->str = single_quotes(line, data->str, &(data->i));

		}
	}
}

void	add_free(t_data *data, t_token **token)
{
	ft_tokenadd_back(token, new_token(data->str, get_type(data->str)));
	free(data->str);
	data->str= NULL;
}