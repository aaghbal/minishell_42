/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect22.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:55:00 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/08 11:58:31 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_2(t_arg *tmp)
{
	int	file_d;

	file_d = 0;
	if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, ">>", 3))
	{
		file_d = open(tmp->next->next->redfile, O_CREAT
				| O_RDWR | O_APPEND, 0644);
		dup2(file_d, STDOUT_FILENO);
	}
	else if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, ">", 2))
	{
		file_d = open(tmp->next->next->redfile, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
		dup2(file_d, STDOUT_FILENO);
	}
	return (file_d);
}
