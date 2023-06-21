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

void	multi_red(t_arg *tmp)
{
	t_arg	*tmp2;
	int		file_d;

	file_d = 0;
	tmp2 = tmp;
	while (tmp2->next && tmp2->next->cmd[0] == '>')
	{
		if (tmp2->next->cmd[1] == '>')
			file_d = open(tmp2->next->redfile, O_CREAT | O_RDWR
					| O_APPEND, 0644);
		else
			file_d = open(tmp2->next->redfile, O_CREAT | O_RDWR
					| O_TRUNC, 0644);
		close(file_d);
		tmp2 = tmp2->next;
	}
}

int	redirect_inpt(t_arg *tmp, int fd[2])
{
	int	file_d;

	if (!ft_strncmp(tmp->next->cmd, ">", 2))
		tmp = tmp->next;
	if (!access(tmp->next->redfile, R_OK))
		file_d = open(tmp->next->redfile, O_RDONLY);
	else
		return (-1);
	dup2(file_d, STDIN_FILENO);
	while (tmp->next && !ft_strncmp(tmp->next->cmd, "<", 2))
	{
		if (access(tmp->next->redfile, R_OK))
			return (-1);
		tmp = tmp->next;
	}
	if (tmp->next && !ft_strncmp(tmp->next->cmd, "|", 2))
		dup2(fd[1], STDOUT_FILENO);
	return (file_d);
}

int	parsing(char *str)
{
	if (check_line(str))
		return (1);
	if (check_line_2(str))
	{
		printf("\e[0;31mminishell : command not found\n");
		g_ext_s = 127;
		return (1);
	}
	return (0);
}
