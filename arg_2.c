/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:21:13 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/05 17:31:00 by aaghbal          ###   ########.fr       */
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
	if (!new)
		exit(0);
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

void	is_echo(t_token **tmp, t_arg **arg, char	**tmp2)
{
	ft_argadd_back(arg, newarg_token(tmp2[0], (*tmp)->type));
	append_word_2(tmp2, arg);
	*tmp = (*tmp)->next;
}

void	is_tokkenword(t_token **tmp, t_arg **arg)
{
	if ((*tmp && (*tmp)->type == tokenword) || (*tmp)->key == 1)
	{
		ft_argadd_back(arg, newarg_token((*tmp)->cmd, (*tmp)->type));
		(*tmp) = (*tmp)->next;
		append_word(tmp, arg);
	}
	if ((*tmp) && (*tmp)->type == redirections && (*tmp)->key == 0)
		apend_redirection(tmp, arg);
}
