/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:55:17 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/26 18:30:04 by aaghbal          ###   ########.fr       */
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
		return (1);
	return (0);
}

char *get_token_pars(char *line)
{
	int i;
	
	if (!line)
		return (NULL);
	i = 0;
	if (line[i] && (line[i] == '<' || line[i] == '>') 
		&& (line[i + 1] != '<' && line[i + 1] != '>'))
		return ft_substr(line, 0, 1);
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<')
	|| (line[i] == '>' && line[i + 1] == '>')))
		return ft_substr(line, 0, 2);
	return NULL;
}

int ft_parsing(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			if (check_quotes(tmp, &i))
				return(1);
		i++;
	}
	return (0);
}

int	ft_parsing_2(t_token **token)
{
	t_token *tmp;
	t_token *tmp1;

	tmp = *token;
	tmp1 = *token;
	int c = 1;
	if (tmp1->cmd != NULL)
	{
		if (get_token(ft_tokenlast(tmp1)->cmd))
			return (1);
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "|", 1) && c == 1)
			return (1);
		c = 0;
		if (get_token_pars(tmp->cmd)
		&& get_token_pars(tmp->next->cmd))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

