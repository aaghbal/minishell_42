/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:32:27 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/14 13:32:28 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

	while (((*tmp) && ((*tmp)->type == tokenword || (*tmp)->key == 1)))
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
	printf("! = %s\n", tmp[i]);
	while (tmp[i])
	{
		tmp2 = ft_arglast(*arg);
		tmp2->arg = alloc_arg(tmp2->arg, tmp[i]);
		i++;
	}
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
	char	**tmp2;

	while (tmp)
	{
		tmp2 = ft_split(tmp->cmd, ' ');
		if (tmp2[1] && ft_strncmp(tmp->cmd, "echo", 5))
		{
			ft_argadd_back(arg, newarg_token(tmp2[0], (tmp)->type));
			append_word_2(tmp2, arg);
			tmp = tmp->next;
		}
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

void	free_tabb(char **tabb)
{
	int	i;

	i = 0;
	while (tabb && tabb[i])
		free(tabb[i++]);
	free(tabb);
}

void	free_list(t_token *tabb)
{
	while (tabb->next)
	{
		if (tabb->cmd)
			free(tabb->cmd);
		if (tabb)
			free(tabb);
		tabb = tabb->next;
	}
	if (tabb->cmd[0])
		free(tabb->cmd);
	if (tabb)
		free(tabb);
}

void	free_arg(t_arg *str)
{
	while (str)
	{
		free(str->cmd);
		free_tabb(str->arg);
		free(str);
		if (str->redfile)
			free(str->redfile);
		str = str->next;
	}
}
