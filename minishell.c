/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:49:22 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/06 10:49:24 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **spl)
{
	int i;
	for (i = 0; spl[i]; i++);
	for (int j = 0; j < i; j++)
		printf("%s\n", spl[j]);
}

char *append_char(char *str, char c)
{
	char *res;
	char tmp[2];
	if (!str)
	{
		res = malloc(sizeof(char) * 2);
		res[0] = c;
		res[1] = '\0';
	}
	else
	{
		tmp[0] = c;
		tmp[1] = '\0';
		res = malloc(sizeof(char) * ft_strlen(str) + 2);
		res = ft_strjoin(str, tmp);
	}
	return res;
}

int is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

e_type get_type(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (tokenPipe);
	else if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (redirections);
	return (TokenWord);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_tokenlast(*lst);
			p->next = new;
		}
	}
}

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
		while (line[i] && !is_token(line[i]) && line[i] != ' ')
			str = append_char(str, line[i++]);
		if (str && line[i] == ' ')
		{
			ft_tokenadd_back(&token, new_token(str, get_type(str)));
			free(str);
			str = NULL;
		}
		if (is_token(line[i]) && line[i] != ' ')
		{
			str = char_to_str(&line[i]);
			ft_tokenadd_back(&token, new_token(str, get_type(str)));
			if (str)
				free(str);
		}
		i++;
	}
	if (str && line[i] == '\0')
	{
		ft_tokenadd_back(&token, new_token(str, get_type(str)));
		free(str);
	}
	t_token *tmp = token;
	while (tmp)
	{
		if (tmp)
			printf("##%s = [%s]\n", tmp->cmd, print_token(tmp->typee));
		tmp = tmp->next;
	}
}

int main(int ac, char ** av, char *envp[])
{
	(void)ac;
	(void)av;
	(void)envp;
	char *input;

	while (1)
	{

		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		token_line(input);
		free(input);
	}
	return (0);
}
