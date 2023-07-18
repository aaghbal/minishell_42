/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:04 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/08 10:02:05 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_handler(int s)
{
	dup2(s, STDIN_FILENO);
	close(s);
}

void	execute1(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	static int	s;
	int			fd[2];
	int			fd2[2];
	int			pid;

	pipe(fd);
	pipe(fd2);
	pid = fork();
	if (pid == -1)
		perror("Error");
	signal(2, sighandler_child);
	if (pid == 0)
	{
		execute_child(tmp, fd, fd2, s);
		if (s)
			s_handler(s);
		if (!ft_strncmp(tmp->cmd, "<", 2) || (!ft_strncmp(tmp->cmd, "<<", 3)
				&& tmp->redfile))
			no_cmd_inpt(tmp, export_list, env_list);
		all_cmd(tmp, export_list, env_list);
	}
	s = parent(0, s, fd);
	if (execute_parent(tmp, fd, fd2, s))
		s = reset(pid);
}

t_arg	*exe1(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	if (tmp && get_next_red(tmp) > 1)
		multi_red(tmp);
	execute1(tmp, export_list, env_list);
	if (!ft_strncmp(tmp->cmd, "<", 2))
	{
		while (tmp)
		{
			if (tmp->cmd && (tmp->cmd[0] == '|'
					|| !ft_strncmp(tmp->cmd, "<<", 3)))
				break ;
			tmp = tmp->next;
		}
	}
	else if (hered_check(tmp))
	{
		wait(0);
		while (tmp && tmp->cmd && tmp->cmd[0] != '|')
			tmp = tmp->next;
	}
	else
		tmp = tmp->next;
	return (tmp);
}

void	execute2(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	if (tmp && !ft_strncmp(tmp->cmd, "exit", 5))
		tmp = my_exit(tmp);
	if (tmp && tmp->key == 0 && tmp->cmd[0] == '>')
		tmp = first_redirect(tmp);
	while (tmp)
	{
		if (tmp && tmp->cmd[0] == '|')
		{
			if (tmp->next && tmp->next->cmd[0] == '>')
			{
				tmp = first_redirect(tmp->next);
				if (!tmp)
					continue ;
			}
			tmp = tmp->next;
		}
		if (tmp && tmp->key == 0 && ((tmp->cmd[0] == '>')))
			tmp = tmp->next;
		else if (tmp && !ft_strncmp(tmp->cmd, "exit", 5))
			tmp = tmp->next;
		else
			tmp = exe1(tmp, export_list, env_list);
	}
}

void	execute(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tmp->cmd, "export", 7) && tmp->arg[1])
	{
		tmp = if_export(tmp, export_list, env_list);
		if (!tmp)
			return ;
	}
	else if (!ft_strncmp(tmp->cmd, "unset", 6) && tmp->arg[1])
	{
		tmp = if_unset(tmp, export_list, env_list);
		if (!tmp)
			return ;
	}
	else if (!ft_strncmp(tmp->cmd, "cd", 3) && !tmp->next)
	{
		my_cd(tmp, export_list, env_list);
		return ;
	}
	execute2(tmp, export_list, env_list);
	while (wait(0) != -1)
		;
}
