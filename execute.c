/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:04 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:09:00 by zel-kach         ###   ########.fr       */
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

void	multi_inptred(t_arg *tmp)
{
	t_arg	*tmp2;
	int		file_d;

	file_d = 0;
	tmp2 = tmp;
	while (tmp2->next && !ft_strncmp(tmp->next->cmd, "<", 2))
	{
		file_d = open(tmp2->next->redfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		close(file_d);
		tmp2 = tmp2->next;
	}
}

void	execute1(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	int			fd[2];
	int			fd2[2];
	static int	s;
	int			pid;

	pipe(fd);
	pipe(fd2);
	pid = fork();
	if (pid == 0)
	{
		if (hered_check(tmp))
		{
			file_d = here_doc(tmp, fd2);
			if (get_next_pip(tmp))
				dup2(fd[1], STDOUT_FILENO);
			dup2(fd2[0], STDIN_FILENO);
			close_file(file_d, fd2);
			close_file(file_d, fd);
			if (tmp->cmd[0] != '<')
			{
				all_cmd(tmp, export_list, env_list);
			}
			else
				exit (0);
		}
		if (tmp && tmp->next && tmp->next->cmd[0] == '|')
			dup2(fd[1], STDOUT_FILENO);
		else if ((tmp && tmp->next && tmp->next->cmd[0] == '>'))
			file_d = redirect(tmp);
		else if ((tmp && tmp->next && tmp->next->cmd[0] == '<'))
		{
			file_d = redirect_inpt(tmp);
			if (file_d == -1)
			{
				printf ("minishell: %s: No such file or directory\n", tmp->next->redfile);
				close_file(file_d, fd2);
				close_file(file_d, fd);
				exit(1);
			}
			s = 0;
		}
		if (s)
		{
			dup2(s, STDIN_FILENO);
			close(s);
		}
		close_file(file_d, fd2);
		close_file(file_d, fd);
		all_cmd(tmp, export_list, env_list);
	}
	else
	{
		close_file(file_d, fd2);
		s = parent(file_d, s, fd);
	}
	if (!tmp->next)
		s = reset(pid);
}

void	execute2(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	if (tmp->cmd[0] == '>')
	{
		file_d = open(tmp->next->cmd, O_CREAT | O_RDWR, 0644);
		tmp = tmp->next;
		tmp = tmp->next;
	}
	while (tmp)
	{

		if (tmp && tmp->cmd[0] == '|')
		{
			if (tmp->next->cmd[0] == '>')
			{
				open(tmp->next->next->cmd, O_CREAT | O_TRUNC, 0777);
				tmp = tmp->next;
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		else if (tmp && (tmp->cmd[0] == '>' || !ft_strncmp(tmp->cmd, "<", 2)))
			tmp = tmp->next;
		else if (tmp && !ft_strncmp(tmp->cmd, "exit", 5))
			my_exit(tmp);
		else
		{
			if (tmp && get_next_red(tmp) > 1) // ??? | >
				multi_red(tmp);
			if (tmp && get_next_red(tmp) > 1) // ??? | >
				multi_red(tmp);
			execute1(tmp, export_list, env_list, file_d);
			if (hered_check(tmp))
			{
				wait(0);
				while (tmp)
				{
					if (tmp->cmd[0] == '|')
					{
						tmp = tmp->next;
						break ;
					}
					tmp = tmp->next;
				}
			}
			else
				tmp = tmp->next;
		}
	}
}

void	execute(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	file_d;

	file_d = 0;
	if (!get_next_pip(tmp) && !ft_strncmp(tmp->cmd,
			"export", 7) && tmp->arg[1])
	{
		my_export(export_list, env_list, tmp->arg[1]);
		return ;
	}
	else if (!get_next_pip(tmp) && !ft_strncmp(tmp->cmd,
			"unset", 6) && tmp->arg[1])
	{
		my_unset(tmp->arg[1], export_list, env_list);
		return ;
	}
	else if (!ft_strncmp(tmp->cmd, "cd", 3) && !tmp->next)
	{
		my_cd(tmp);
		return ;
	}
	execute2(tmp, export_list, env_list, file_d);
	while (wait(0) != -1 || errno != ECHILD)
		tmp = NULL;
}
