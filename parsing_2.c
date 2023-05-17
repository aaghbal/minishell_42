/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:55:17 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/15 16:55:19 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *tmp, int *i)
{
	char c;
	int	 j;
	char chara;

	c = tmp[*i];
	j = (*i) + 1;
	if (tmp[*i] == '\'')
		chara = '\"';
	else
		chara = '\'';
	while (tmp[j])
	{
		if (tmp[j] == chara)
			tmp[j] = '#';
		if(tmp[j] == c)
		{
			tmp[j] = '#';
			break;
		}
		j++;
	}
	if (tmp[j] != '#')
		return (0);
	return (1);
}

int ft_parsing(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			if (check_quotes(tmp, &i) == 0)
				return(0);
		i++;
	}
	return (1);
}

int	ft_parsing_2(t_token **token)
{
	t_token *tmp;
	t_token *tmp1;

	tmp = *token;
	tmp1 = *token;
	int c = 1;
	if (get_token(ft_tokenlast(tmp1)->cmd))
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->cmd, "|", 1) == 0 && c == 1)
			return (0);
		c = 0;
		if (get_token(tmp->cmd)
		&& get_token(tmp->next->cmd)) 
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

