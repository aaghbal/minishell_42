/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:19:13 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/29 16:18:25 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_token	*tmp;

	while (tabb->next)
	{
		tmp = tabb->next;
		if (tabb->cmd)
			free(tabb->cmd);
		if (tabb)
			free(tabb);
		tabb = tmp;
	}
	if (tabb->cmd[0])
		free(tabb->cmd);
	if (tabb)
		free(tabb);
}

void	free_arg(t_arg *str)
{
	t_arg	*tmp;

	while (str)
	{
		tmp = str->next;
		free(str->cmd);
		free_tabb(str->arg);
		if (str->redfile)
			free(str->redfile);
		free(str);
		str = tmp;
	}
}
