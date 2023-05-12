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


char	*quotes(char *line,char *str, int *len)
{
	int on;
	int	i;

	on = 1;
	i = *len;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t' || is_token(line[i])) && on == 0)
		{
			*len = i;
			break;
		}
		if (line[i] == '\"')
			on = 0;
		else
			str = append_char(str, line[i]);
		i++;
	}
	*len = i;
	return (str);
}

char	*single_quotes(char *line,char *str, int *len)
{
	int on;
	int	i;

	on = 1;
	i = *len;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t' || is_token(line[i])) && on == 0)
		{
			*len = i;
			break;
		}
		if (line[i] == '\'')
			on = 0;
		else
			str = append_char(str, line[i]);
		i++;
	}
	*len = i;
	return (str);
}

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
	node->typee = type;
	node->next = NULL;
	return (node);
}

int is_char(char c)
{
	return (c == ' ' || c == '\t' || is_token(c));
}

char *get_token(char *line)
{
	int i;

	i = 0;
	if (line[i] && (line[i] == '|' || line[i] == '<' || line[i] == '>') && (line[i + 1] != '<' && line[i + 1] != '>'))
		return ft_substr(line, 0, 1);
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
	{
		return ft_substr(line, 0, 2);
	}
	return NULL;

}

void token_line(char *line)
{
	int		i;
	char	*str;
	char	*new;
	t_token	*token;

	str = NULL;
	token = NULL;
	new= NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (is_token(line[i]))
		{
			str = get_token(&line[i++]);
			if (ft_strlen(str) == 2)
				i++;
		}
		else if (line[i] == '\"')
			str = quotes(line, str, &i);
		else if (line[i] == '\'')
			str = single_quotes(line, str, &i);
		else
		{
			while (line[i] && !is_char(line[i]))
			{
				if (line[i] != '\"' && line[i] != '\'')
					str = append_char(str, line[i++]);
				else
					str = quotes(line, str, &i);
			}
		}
		if (str)
		{
			ft_tokenadd_back(&token, new_token(str, get_type(str)));
			free(str);
			str= NULL;
		}
	}
	t_token *tmp = token;
	while (tmp)
	{
		if (tmp)
			printf("%s = [%s]\n", tmp->cmd, print_token(tmp->typee));
		tmp = tmp->next;
	}
}
