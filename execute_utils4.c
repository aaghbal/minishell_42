/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:26:26 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/26 17:26:29 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*if_redi(t_arg *tmp)
{
	if (tmp && tmp->cmd[0] == '>')
	{
		while (tmp && tmp->cmd[0] == '>')
		{
			if (tmp && tmp->cmd && tmp->cmd[0] == '|')
				exit (0);
			tmp = tmp->next;
		}
	}
	return (tmp);
}
