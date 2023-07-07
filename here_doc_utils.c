/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:39 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 12:22:26 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc(t_arg *file)
{
	int		i;
	char	**delem;

	i = 0;
	while (ft_strncmp(file->cmd, "<<", 3))
		file = file->next;
	while (file && !ft_strncmp(file->cmd, "<<", 3))
	{
		i++;
		file = file->next;
	}
	delem = malloc(sizeof(char *) * i + 1);
	if (!delem)
		exit(0);
	return (delem);
}

int	hered_check(t_arg *tmp)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "|", 2))
			return (0);
		if (!ft_strncmp(tmp->cmd, "<<", 3) && tmp->key == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
