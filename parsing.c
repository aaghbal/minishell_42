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

void	double_cout(int *i, char	*line, t_token	**token)
{
	char *str;
	int c = 0;
	int l = 0;

	str = NULL;
	(*i)++;
	c++;
	while(line[(*i)++] == '\"' && line[(*i)])
		c++;
	while (line[(*i)] != '\"' && line[(*i)])
	{
		str = append_char(str, line[(*i)]);
		(*i)++;
	}
	while(line[(*i)] == '\"' && line[(*i)])
	{
		(*i)++;
		l++;
	}
	if (c == l && line[(*i) - 1])
		ft_tokenadd_back(token, new_token(str, get_type(str)));
	free(str);
	str = NULL;
}
void	single_cout(int *i, char	*line, t_token	**token)
{
	char *str;

	str = NULL;
	(*i)++;
	while (line[*i] == '\''  && line[*i])
		(*i)++;
	while (line[*i] != '\''  && line[*i])
		str = append_char(str, line[(*i)++]);
	while (line[*i] == '\''  && line[*i])
		(*i)++;
	ft_tokenadd_back(token, new_token(str, get_type(str)));
	free(str);
	str = NULL;
	(*i)++;
}

void	default_cmd(int *i, char	*line, t_token	**token)
{
	char	*str;

	str = NULL;
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