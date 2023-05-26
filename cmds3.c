/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:04 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 21:36:02 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_file(int file_d, int fd[2])
{
	if (file_d)
		close(file_d);
	close(fd[1]);
	close(fd[0]);
}

void	multi_red(t_arg *tmp)
{
	t_arg	*tmp2;
	int		file_d;

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

void	execute1(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	int			fd[2];
	static 		int	s;
	int			pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (tmp->next && tmp->next->cmd[0] == '|')
			dup2(fd[1], 1);
		else if (tmp->next && tmp->next->cmd[0] == '>')
			file_d = redirect(tmp);
		if (s > 0)
		{
			dup2(s, 0);
			close(s);
		}
		close_file(file_d, fd);
		all_cmd(tmp, export_list, env_list);
	}
	else
	{
		if (s > 0)
			close(s);
		s = dup(fd[0]);
		close_file(file_d, fd);
	}
	if (tmp->next == NULL)
		waitpid(pid, &g_ext_s, 0);
}

void	execute2(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	while (tmp)
	{
		if (tmp->cmd[0] == '|' || tmp->cmd[0] == '>')
		{
			tmp = tmp->next;
		}
		else if (!ft_strncmp(tmp->cmd, "exit\0", 5))
			my_exit();
		else
		{
			if (get_next_red(tmp) > 1)
				multi_red(tmp);
			execute1(tmp, export_list, env_list, file_d);
			tmp = tmp->next;
		}
	}
}

void	execute(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	file_d;

	file_d = 0;
	if (!get_next_pip(tmp) && !ft_strncmp(tmp->cmd,
			"export\0", 7) && tmp->arg[1])
	{
		my_export(export_list, env_list, tmp->arg[1]);
		return ;
	}
	else if (!get_next_pip(tmp) && !ft_strncmp(tmp->cmd,
			"unset\0", 6) && tmp->arg[1])
	{
		my_unset(tmp, export_list, env_list);
		return ;
	}
	execute2(tmp, export_list, env_list, file_d);
	while (wait(0) != -1 || errno != ECHILD)
		tmp = NULL;
}
