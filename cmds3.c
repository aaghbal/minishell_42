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
	int		file_d = 0;

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

void	here_doc(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	fd[2];
	char *delimiter;
	int file_d = 0;

	pipe(fd);
	if (!fork())
	{
		signal(11, doc_handler);
		signal(2, doc_handler);
		if (tmp->cmd[0] == '<')
		{
			delimiter = ft_strdup(tmp->next->cmd);
			char *input = readline(">");
			while (1)
			{
				if (!ft_strncmp(delimiter, input, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(delimiter)))
					break ;
				ft_putendl_fd(input, fd[1]);
				input = readline(">");
			}
			if (tmp->next->next && tmp->next->next->cmd[0] == '>')
				file_d = redirect(tmp->next);
		}
		else
		{
			if (tmp->next && tmp->next->cmd[0] == '>')
				delimiter = ft_strdup(tmp->next->next->redfile);
			else
				delimiter = ft_strdup(tmp->next->redfile);
			char *input = readline(">");
			while (1)
			{
				if (!ft_strncmp(delimiter, input, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(delimiter)))
					break ;
				ft_putendl_fd(input, fd[1]);
				input = readline(">");
			}
			if (tmp->next && tmp->next->cmd[0] == '>')
				file_d = redirect(tmp);
		}
		dup2(fd[0], 0);
		close_file(file_d, fd);
		if (tmp->cmd[0] != '<')
			all_cmd(tmp, export_list, env_list);
		else
			exit (0);
	}
	else
		close_file(file_d, fd);
	// wait(0); ??????????????????
}

void	execute1(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	int			fd[2];
	static int	s;
	int			pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (tmp->next && tmp->next->cmd[0] == '|')
			dup2(fd[1], 1);
		else if ((tmp->next && tmp->next->cmd[0] == '>'))
			file_d = redirect(tmp);
		if (s)
		{
			dup2(s, 0);
			close(s);
		}
		close_file(file_d, fd);
		all_cmd(tmp, export_list, env_list);
	}
	else
	{
		if (s)
			close(s);
		s = dup(fd[0]);
		close_file(file_d, fd);
	}
	if(!tmp->next)
	{
		s = 0;
		waitpid(pid, &g_ext_s, 0);
		g_ext_s = WEXITSTATUS(g_ext_s);
	}
}

int	hered_check(t_arg *tmp)
{
	while (tmp && tmp->cmd[0] != '|')
	{
		if (!ft_strncmp(tmp->cmd, "<<", 3))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	execute2(t_arg *tmp, t_list *export_list, t_list *env_list, int file_d)
{
	if (tmp->cmd[0] == '>')
	{
		file_d = open(tmp->next->cmd, O_CREAT | O_RDWR , 0644);
		tmp = tmp->next;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (hered_check(tmp))
		{
			here_doc(tmp, export_list, env_list);
			while (1)
			{
				if (!tmp || tmp->cmd[0] == '|')
					break ;
				tmp = tmp->next;
			}
		}
		else if (tmp->cmd[0] == '|')
		{
			if (tmp->next->cmd[0] == '>')
			{
				open(tmp->next->next->cmd, O_CREAT | O_TRUNC, 0777);
				tmp = tmp->next;
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		else if (tmp->cmd[0] == '>')
			tmp = tmp->next;
		else if (!ft_strncmp(tmp->cmd, "exit", 5))
			my_exit(tmp);
		else
		{
			if (get_next_red(tmp) > 1) // ??? | >
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
	else if (!ft_strncmp(tmp->cmd, "cd", 3) && !tmp->next)
	{
		my_cd(tmp);
		return ;
	}
	execute2(tmp, export_list, env_list, file_d);
	while (wait(0) != -1 || errno != ECHILD)
		tmp = NULL;
}
