/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:10:29 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redirect(t_arg *tmp)
{
	int	file_d;

	if (tmp->next->cmd[1] == '\0')
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(file_d, STDOUT_FILENO);
	return (file_d);
}

int	redirect_inpt(t_arg *tmp)
{
	int	file_d;

	if (!access(tmp->next->redfile, R_OK))
		file_d = open(tmp->next->redfile, O_RDONLY);
	else
		return (-1);
	dup2(file_d, STDIN_FILENO);
	while (tmp->next)
	{
		if (!access(tmp->next->redfile, R_OK));
		else
			return (-1);
		tmp = tmp->next;
	}
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
