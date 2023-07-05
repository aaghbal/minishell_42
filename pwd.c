/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 02:56:01 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/05 19:48:44 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_list *expo)
{
	char	**tmp2;
	t_list	*head;

	head = expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(tmp2[0], "PWD", ft_strlen(tmp2[0]))
			&& ft_strlen(tmp2[0]) == ft_strlen("PWD"))
		{
			head->content = ft_substr(head->content, 0, ft_strlen("PWD="));
			head->content = ft_strjoin(head->content, getcwd(NULL, 0));
		}
		free_tabb(tmp2);
		head = head->next;
	}
}

void	ft_oldpwd(t_list *expo)
{
	char	**tmp2;
	t_list	*head;

	head = expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (head->content && !ft_strncmp(tmp2[0], "OLDPWD", ft_strlen(tmp2[0]))
			&& ft_strlen(tmp2[0]) == ft_strlen("OLDPWD"))
		{
			head->content = ft_substr(head->content, 0, ft_strlen("OLDPWD="));
			head->content = ft_strjoin(head->content, getcwd(NULL, 0));
		}
		free_tabb(tmp2);
		head = head->next;
	}
}

int	token_found(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
