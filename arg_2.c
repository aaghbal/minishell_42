/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:21:13 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/23 22:27:10 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_arg(t_token *tmp, t_arg **arg)
{
	char	**tmp2;

	while (tmp)
	{
		tmp2 = ft_split(tmp->cmd, ' ');
		if (tmp2[1] && ft_strncmp(tmp->cmd, "echo", 5))
			append_echo(tmp, arg, tmp2);
		else if (tmp->type == tokenword || tmp->key == 1)
		{
			if ((tmp && tmp->type == tokenword) || tmp->key == 1)
			{
				ft_argadd_back(arg, newarg_token((tmp)->cmd, (tmp)->type));
				(tmp) = (tmp)->next;
				append_word(&tmp, arg);
			}
			if (tmp && tmp->type == redirections && tmp->key == 0)
				apend_redirection(&tmp, arg);
		}
		else
		{
			if (tmp)
			{
				if (!(ft_strncmp(tmp->cmd, "<<", 3)) && tmp->key == 0)
					apend_redirection(&tmp, arg);
				else
				{
					ft_argadd_back(arg, newarg_token(tmp->cmd, tmp->type));
					tmp = tmp->next;
				}
			}
		}
		free_tabb(tmp2);
	}
}

char	**alloc_arg(char **args, char *cmd)
{
	char	**new;
	int		i;

	i = 0;
	while (args && args[i++])
		;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args && args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i++] = ft_strdup(cmd);
	new[i] = NULL;
	free_tabb(args);
	return (new);
}

t_arg	*ft_arglast(t_arg *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
