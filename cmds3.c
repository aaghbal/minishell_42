/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:04 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:05 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_exec_cmd_e1(t_arg *cmd, int pi)
{
	int		file_d;
	char	*ppp[4];
	int		save_out;

	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[2] = cmd->arg[2];
	ppp[3] = NULL;
	file_d = 0;
	save_out = dup(fileno(stdout));
	if (pi == APND)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND | 0644);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC | 0644);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd->cmd, ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->cmd), ppp, NULL) == -1)
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
	dup2(save_out, fileno(stdout));
	wait(0);
}

//redirect filename with flag
void	my_exec_cmd_d1(t_arg *cmd, int pi)
{
	int		file_d;
	char	*ppp[3];
	int		save_out;

	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[2] = NULL;
	file_d = 0;
	save_out = dup(fileno(stdout));
	if (pi == APND)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND | 0644);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC | 0644);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd->cmd, ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->cmd), ppp, NULL) == -1)
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
	dup2(save_out, fileno(stdout));
	wait(0);
}

void	my_exec_cmd(t_arg *cmd, int pi)
{
	static int current_pipe = -1;
	if (pi == NOR || pi == PIPE ||pi == FPIPE ||pi == EPIPE)
	{
		if (pi != NOR)
			current_pipe++;
		if (!cmd->arg[1])
			my_exec_cmd_a1(cmd, pi, current_pipe);
		else if (!cmd->arg[2])
			my_exec_cmd_b1(cmd, pi, current_pipe);
		else
			my_exec_cmd_c1(cmd, pi, current_pipe);
	}
	else if (pi == APND || pi == TRNC)
	{
		if (!cmd->arg[1])
			my_exec_cmd_c2(cmd, pi);
		else if (!cmd->arg[4])
			my_exec_cmd_d1(cmd, pi);
		else if (!cmd->arg[5])
			my_exec_cmd_e1(cmd, pi);
	}
	// else
	// {
	// 	if (!cmd->arg[1])
	// 		my_exec_cmd_a1(cmd);
	// 	else if (!cmd->arg[2])
	// 		my_exec_cmd_b1(cmd, pi);
	// 	else
	// 		my_exec_cmd_c1(cmd);
	// }
}


	// 	
	// 	save_out = dup(fileno(stdout));
	// 	dup2(g_fd[1], 1);
	// 	printf ("%s\n", pwd);
	// 	close(g_fd[1]);
	// 	dup2(save_out, fileno(stdout));
	// }


//command 											1
//command file_name									2
//command flag										2
//command flag file_name 							3

//command redirecit file_name 						3	
//command flag redirecit file_name 					 4
//command flag file_name redirect file_name			5
