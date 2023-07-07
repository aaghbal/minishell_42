/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:13:06 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 11:29:17 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_r_inpt(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	int	file_d;

	file_d = 0;
	if (s)
		close (s);
	file_d = r_inpt(tmp, fd, fd2);
	return (file_d);
}

int	execute_child_2(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	if (hered_check(tmp))
	{
		if (s)
			close (s);
		return (execute_hered(tmp, fd, fd2), 1);
	}
	if (tmp && tmp->cmd[0] == '|')
	{
		s = current_pipe(tmp, fd, fd2, s);
		exit (0);
	}
	return (0);
}

int	execute_child(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	int	file_d;
	int	file_d2;

	file_d = 0;
	file_d2 = 0;
	if (execute_child_2(tmp, fd, fd2, s))
		return (1);
	if (tmp && tmp->next && tmp->next->cmd[0] == '|')
		dup2(fd[1], STDOUT_FILENO);
	else if ((tmp->next && tmp->next->cmd[0] == '>'))
	{
		if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, "<", 2))
			file_d = if_r_inpt(tmp, fd, fd2, s);
		file_d2 = redirect(tmp);
	}
	else if ((tmp->next && !ft_strncmp(tmp->next->cmd, "<", 2)))
		file_d = if_r_inpt(tmp, fd, fd2, s);
	else if ((tmp && !ft_strncmp(tmp->cmd, "<", 2)))
	{
		file_d = r_inpt2(tmp, fd, fd2);
		file_d2 = redirect2(tmp);
	}
	return (close_file(file_d, fd2), close_file(file_d2, fd), 1);
}

int	execute_parent(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	close_file(0, fd2);
	if (!tmp->next || (tmp->next && tmp->cmd[0] == '|'
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
