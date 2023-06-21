/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:51:54 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_status(int g_ext_s)
{
	if (g_ext_s == 2)
		ft_putendl_fd("", STDERR_FILENO);
	else if (g_ext_s == 3)
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	else if (g_ext_s == 11)
		ft_putendl_fd("Segmentation fault: 11", STDERR_FILENO);
}

int	reset(int pid)
{
	waitpid(pid, &g_ext_s, 0);
	if (WIFEXITED(g_ext_s))
	{
		g_ext_s = WEXITSTATUS(g_ext_s);
		if (g_ext_s == 127)
			printf("\e[0;31mminishell: cmmand not found\n");
	}
	else if (WIFSIGNALED(g_ext_s))
	{
		g_ext_s = WTERMSIG(g_ext_s) + 128;
		sig_status(g_ext_s - 128);
	}
	return (0);
}

int	parent(int file_d, int s, int fd[2])
{
	if (s)
		close(s);
	s = dup(fd[0]);
	close_file(file_d, fd);
	return (s);
}

void	close_file(int file_d, int fd[2])
{
	if (file_d)
		close(file_d);
	close(fd[1]);
	close(fd[0]);
}

int	execute_hered(t_arg *tmp, int fd[2], int fd2[2])
{
	int	file_d;

	file_d = here_doc(tmp, fd2);
	if (get_next_pip(tmp))
		dup2(fd[1], STDOUT_FILENO);
	dup2(fd2[0], STDIN_FILENO);
	close_file(file_d, fd2);
	close_file(file_d, fd);
	if (tmp->cmd[0] != '<')
		return (1);
	else
		exit (0);
}
