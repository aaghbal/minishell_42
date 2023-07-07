/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 12:23:21 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_status(int g_ext_s)
{
	if (g_ext_s == 2)
		ft_putendl_fd("", STDERR_FILENO);
	else if (g_ext_s == 3)
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
}

int	reset(int pid)
{
	waitpid(pid, &g_ext_s, 0);
	if (WIFEXITED(g_ext_s))
	{
		g_ext_s = WEXITSTATUS(g_ext_s);
		if (g_ext_s == 127)
			printf("\e[0;31mminishell: command not found\n");
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

void	check_access(t_arg *tmp)
{
	while (tmp && ft_strncmp(tmp->cmd, "<", 2))
		tmp = tmp->next;
	while (tmp && !ft_strncmp(tmp->cmd, "<", 2))
	{
		if (access(tmp->redfile, R_OK))
		{
			printf ("minishell: No such file or directory\n");
			exit (1);
		}
		tmp = tmp->next;
	}
}

int	execute_hered(t_arg *tmp, int fd[2], int fd2[2])
{
	int		file_d;

	file_d = 0;
	here_doc(tmp, fd2);
	if (get_next_inptred(tmp))
		check_access(tmp);
	if (tmp->next && tmp->next->cmd[0] == '>')
		file_d = redirect(tmp);
	else if (get_next_pip(tmp))
		dup2(fd[1], STDOUT_FILENO);
	dup2(fd2[0], STDIN_FILENO);
	close_file(file_d, fd2);
	close_file(file_d, fd);
	if (tmp->cmd[0] != '<')
		return (1);
	else
		exit (0);
}
