/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:17 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//command only
void	my_exec_cmd_a1(t_arg *cmd, int pi, int current_pipe)
{
	char	*ppp[3];
	int		save_out = 0;
	int		save_in = 0;

	ppp[0] = cmd->arg[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	if (!fork())
	{
		if (pi == FPIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			while(cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == PIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//  [p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == EPIPE)
		{
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//[p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				close(g_fd[cmd->t_pipes][1]);
				cmd->t_pipes--;
			}
		}
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == FPIPE)
		close(g_fd[current_pipe + 1][1]);
	else if (pi == PIPE)
	{
		close(g_fd[current_pipe + 1][1]);
		close(g_fd[current_pipe][0]);
	}
	else if (pi == EPIPE)
	{
		close(g_fd[current_pipe][0]);
		dup2(save_out, STDOUT_FILENO);
		dup2(save_in, STDIN_FILENO);
	}
	wait(0);;
}

void	my_exec_cmd_b1(t_arg *cmd, int pi, int current_pipe)
{
	char	*ppp[3];
	int		save_out = 0;
	int		save_in = 0;

	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[2] = NULL;
	save_out = dup(STDOUT_FILENO);
	save_in = dup(STDIN_FILENO);
	if (!fork())
	{
		if (pi == FPIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			while(cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == PIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//  [p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == EPIPE)
		{
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//[p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				close(g_fd[cmd->t_pipes][1]);
				cmd->t_pipes--;
			}
		}
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == FPIPE)
		close(g_fd[current_pipe + 1][1]);
	else if (pi == PIPE)
	{
		close(g_fd[current_pipe + 1][1]);
		close(g_fd[current_pipe][0]);
	}
	else if (pi == EPIPE)
	{
		close(g_fd[current_pipe][0]);
		dup2(save_out, STDOUT_FILENO);
		dup2(save_in, STDIN_FILENO);
	}
	wait(0);
}

void	my_exec_cmd_c1(t_arg *cmd, int pi, int current_pipe)
{
	char	*ppp[4];
	int		save_out = 0;
	int		save_in = 0;

	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[1] = cmd->arg[2];
	ppp[2] = NULL;
	if (!fork())
	{
		if (pi == FPIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			while(cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == PIPE)
		{
			dup2(g_fd[current_pipe + 1][1], STDOUT_FILENO);// [p + 1][1]
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//  [p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe + 1)
					close(g_fd[cmd->t_pipes][1]);
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				cmd->t_pipes--;
			}
		}
		else if (pi == EPIPE)
		{
			dup2(g_fd[current_pipe][0], STDIN_FILENO);//[p][0]
			while (cmd->t_pipes >= 0)
			{
				if (cmd->t_pipes != current_pipe)
					close(g_fd[cmd->t_pipes][0]);
				close(g_fd[cmd->t_pipes][1]);
				cmd->t_pipes--;
			}
		}
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == FPIPE)
		close(g_fd[current_pipe + 1][1]);
	else if (pi == PIPE)
	{
		close(g_fd[current_pipe + 1][1]);
		close(g_fd[current_pipe][0]);
	}
	else if (pi == EPIPE)
	{
		close(g_fd[current_pipe][0]);
		dup2(save_out, STDOUT_FILENO);
		dup2(save_in, STDIN_FILENO);
	}
	wait(0);
}

//redirect filename no flag
void	my_exec_cmd_c2(t_arg *cmd, int pi)
{
	int		file_d;
	char	*ppp[3];

	ppp[0] = cmd->arg[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	file_d = 0;
	if (pi == TRNC)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC | 0644);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND | 0644);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	close(file_d);
	wait(0);
}
