/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:13:45 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/08 17:13:47 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


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

int check_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

t_type get_type(char *str)
{
	if (!str)
		return (NONE);
	if (!ft_strncmp(str, "|", 1))
		return (tokenpipe);
	else if (!ft_strncmp(">", str, 1) || !ft_strncmp("<", str, 1))
		return (redirections);
	return (tokenword);
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
