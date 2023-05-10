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
	t_token	*token;

	str = NULL;
	token = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '\"')
			double_cout(&i, line, &token);
		else if (line[i] == '\'')
			single_cout(&i, line, &token);
		if (line[i] != '\0')
			default_cmd(&i, line, &token);
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
