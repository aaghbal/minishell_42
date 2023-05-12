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

// void	double_cout(int *i, char	*line, t_token	**token)
// {
// 	char *str;
// 	int c = 0;
// 	int l = 0;

// 	str = NULL;
// 	(*i)++;
// 	c++;
// 	while(line[(*i)] == '\"' && line[(*i)])
// 	{
// 		(*i)++;
// 		c++;
// 	}
// 	while (line[(*i)] != '\"' && line[(*i)])
// 	{
// 		str = append_char(str, line[(*i)]);
// 		(*i)++;
// 	}
// 	while(line[(*i)] == '\"' && line[(*i)])
// 	{
// 		(*i)++;
// 		l++;
// 	}
// 	if (c == l && line[(*i) - 1])
// 		ft_tokenadd_back(token, new_token(str, get_type(str)));
// 	free(str);
// 	str = NULL;
// }

char * char_to_str(char *line)
{
	char *str;
	if ((line[0] == '<' && line[1] == '<') || (line[0] == '>' && line[1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		str[0] = line[0];
		str[1] = line[1];
		str[2] = '\0';
	}
	else
	{
		str = malloc(sizeof(char )* 2);
		str[0] = line[0];
		str[1] = '\0';
	}
	return str;
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

void token_line(char *line)
{
	int		i;
	char	*str;
	char	*newstr;
	t_token	*token;

	str = NULL;
	newstr = NULL;
	token = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		 if (line[i] == '\"')
		{
			i++;
			str  = double_quotes(&i, line, &token, str);
			ft_tokenadd_back(&token, new_token(str, get_type(str)));
			free(str);
			str = NULL;
			
		}
		else if (line[i] == '\'')
		{
			i++;
			str  = single_quotes(&i, line, &token, str);
			ft_tokenadd_back(&token, new_token(str, get_type(str)));
			free(str);
			str = NULL;
		}
		if (line[i] != '\"' && line[i] != '\'')
			default_cmd(&i, line, &token, str);
		i++;
	}
	t_token *tmp = token;
	while (tmp)
	{
		if (tmp)
			printf("%s = [%s]\n", tmp->cmd, print_token(tmp->typee));
		tmp = tmp->next;
	}
}
