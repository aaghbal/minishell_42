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

char **alloc_arg(char **args, char *cmd)
{
	char **new;
	int i = 0;

	while (args && args[i++]);
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args && args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i++] = ft_strdup(cmd);
	new[i] = NULL;
	free_tab(args);
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

t_arg * newarg_token(char *cmd, e_type type)
{
	t_arg *node;

	node = (t_arg *)malloc(sizeof(t_arg));
	node->cmd = ft_strdup(cmd);
	node->arg = alloc_arg(NULL, cmd);
	node->type = type;
	node->next = NULL;
	return (node);
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
 
void	is_arg(t_token *tmp, t_arg **arg)
{
	while (tmp)
	{
		if (tmp->type == TokenWord)
		{
			ft_argadd_back(arg, newarg_token(tmp->cmd, tmp->type));
			tmp = tmp->next;
			while (tmp && tmp->type == TokenWord)
			{
				ft_arglast(*arg)->arg = alloc_arg(ft_arglast(*arg)->arg, tmp->cmd);
				tmp = tmp->next;
			}
		}
		else
		{
			if (tmp)
			{
				ft_argadd_back(arg, newarg_token(tmp->cmd, tmp->type));
				tmp = tmp->next;
			}
		}
	}
}

 void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

 void	free_list(t_token *tab)
{
	int	i;

	i = 0;
	while (tab)
	{
		free(tab);
		tab = tab->next;
	}
	free(tab);
}
