/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:13:06 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/02 10:13:07 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_child(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	int	file_d;
	int	file_d2;

	file_d = 0;
	file_d2 = 0;
	if (hered_check(tmp))
		return (execute_hered(tmp, fd, fd2), 1);
	if (tmp && tmp->cmd[0] == '|')
	{
		s = current_pipe(tmp, fd, fd2, s);
		exit (0);
	}
	if (tmp && tmp->next && tmp->next->cmd[0] == '|')
		dup2(fd[1], STDOUT_FILENO);
	else if ((tmp->next && tmp->next->cmd[0] == '>'))
	{
		if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, "<", 2))
			file_d2 = r_inpt(tmp, fd, fd2);
		file_d = redirect(tmp);
	}
	else if ((tmp->next && !ft_strncmp(tmp->next->cmd, "<", 2)))
		file_d = r_inpt(tmp, fd, fd2);
	else if ((tmp->next && !ft_strncmp(tmp->cmd, "<", 2)))
		file_d = r_inpt2(tmp, fd, fd2);
	return (close_file(file_d, fd2), close_file(file_d2, fd), 1);
}

int	execute_parent(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	close_file(0, fd2);
	if (!tmp->next || (tmp->cmd[0] == '|'
			&& tmp->next->cmd[0] == '>' && !tmp->next->next->next))
	{
		close_file(0, fd2);
		close_file(0, fd);
		return (close(s), 1);
	}
	else
	{
		while (tmp)
		{
			if (tmp->cmd[0] == '|')
				break ;
			tmp = tmp->next;
			if (!tmp)
			{
				close_file(0, fd2);
				close_file(0, fd);
				return (close(s), 1);
			}
		}
	}
	return (0);
}
