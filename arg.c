/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:32:27 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/29 16:13:13 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*p;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_arglast(*lst);
			p->next = new;
		}
	}
}

void	append_word(t_token **tmp, t_arg **arg)
{
	t_arg	*tmp2;

	while (((*tmp) && ((*tmp)->type == tokenword || (*tmp)->key == 1)) && *arg)
	{
		tmp2 = ft_arglast(*arg);
		tmp2->arg = alloc_arg(tmp2->arg, (*tmp)->cmd);
		(*tmp) = (*tmp)->next;
	}
}

void	append_word_2(char **tmp, t_arg **arg)
{
	int		i;
	t_arg	*tmp2;

	i = 1;
	while (tmp && tmp[i])
	{
		tmp2 = ft_arglast(*arg);
		tmp2->arg = alloc_arg(tmp2->arg, tmp[i]);
		printf("donnne\n");
		i++;
	}
	printf("uesyses\n");
}

void	apend_redirection(t_token **tmp, t_arg **arg)
{
	t_arg	*red;

	red = newarg_token((*tmp)->cmd, (*tmp)->type);
	(*tmp) = (*tmp)->next;
	if ((*tmp) && (!get_token((*tmp)->cmd) || (*tmp)->key) == 1)
		red->redfile = ft_strdup((*tmp)->cmd);
	if ((*tmp) && ft_strncmp((*tmp)->cmd, "<<", 3))
	{
		(*tmp) = (*tmp)->next;
		append_word(tmp, arg);
	}
	if (*tmp && (*tmp)->type == redirections)
		apend_redirection(tmp, arg);
	if (red)
		ft_argadd_back(arg, red);
}

void	is_arg(t_token *tmp, t_arg **arg)
{
	while (tmp)
	{
		if (tmp->type == tokenword || tmp->key == 1)
			is_tokkenword(&tmp, arg);
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
	}
}
