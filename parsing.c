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

char get_next_state(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			return line[i];
		else if (line[i] == '\"')
			return '\"';
		i++;
	}
	return '\"';
}

char	*double_quotes(int *i, char	*line,t_token **token, char *str)
{

	char *newstr;

	newstr = NULL;
	while (line[(*i)] != '\"' && line[(*i)])
	{
		str = append_char(str, line[(*i)]);
		(*i)++;
	}
	if (line[(*i)] && line[*i] == '\"')
		(*i)++;
	if (line[*i] && line[*i] != ' ' && line[(*i)] != '|' && line[*i] != '\"' &&  line[*i] != '\'')
	{
		if (line[*i] && get_next_state(&line[*(i)]) == '\'')
			str = ft_strjoin(str, single_quotes(i, line, token, newstr));
		else
			str = ft_strjoin(str, double_quotes(i, line, token, newstr));
	}
	if (line[(*i)] && line[*i] == '\'')
	{
		(*i)++;
		str = single_quotes(i, line, token, str);
	}
	return(str);
}
char	*single_quotes(int *i, char	*line, t_token	**token, char *str)
{
	char *newstr;

	newstr = NULL;
	while (line[(*i)] != '\'' && line[(*i)])
	{
		str = append_char(str, line[(*i)]);
		(*i)++;
	}
	if (line[(*i)] && line[*i] == '\'')
		(*i)++;
	if (line[*i] && line[*i] != ' ' && line[(*i)] != '|' && line[*i] != '\'' && line[*i] != '\"')
	{
		if (get_next_state(&line[*(i)]) == '\'')
			str = ft_strjoin(str, single_quotes(i, line, token, newstr));
		else
			str = ft_strjoin(str, double_quotes(i, line, token, newstr));
	}
	if (line[(*i)] && line[*i] == '\"')
	{
		(*i)++;
		str = double_quotes(i, line, token, str);
	}
	return(str);
}

void	default_cmd(int *i, char	*line, t_token	**token, char	*str)
{
	while (line[*i] && !is_token(line[*i]) && line[*i] != ' ')
		str = append_char(str, line[(*i)++]);
	if (str && (is_token(line[*i]) || line[*i] == ' ' || line[*i] == '\0'))
	{
		ft_tokenadd_back(token, new_token(str, get_type(str)));
		free(str);
		str = NULL;
	}
	if (is_token(line[*i]) && line[*i] != ' ' && line[*i])
	{
		str = char_to_str(&line[*i]);
		ft_tokenadd_back(token, new_token(str, get_type(str)));
		free(str);
		str = NULL;
	}
}