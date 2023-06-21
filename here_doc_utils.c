/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:39 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/20 16:09:40 by zel-kach         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

char	**alloc(t_arg	*file)
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
	return (delem);
}

int	hered_check(t_arg *tmp)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "<<", 3))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
