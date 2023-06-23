/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:19:13 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/23 22:20:51 by aaghbal          ###   ########.fr       */
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