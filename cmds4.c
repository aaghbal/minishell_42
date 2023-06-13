/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 16:44:48 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redirect(t_arg *tmp)
{
	int	file_d;

	if (tmp->next->cmd[1] == '\0')
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	dup2(file_d, 1);
	return (file_d);
}

int	parsing(char *str)
{
	if (check_line(str))
		return (1);
	if (check_line_2(str))
	{
		free(str);
		printf("\e[0;31mminishell : command not found\n");
		return (1);
	}
	return (0);
}
