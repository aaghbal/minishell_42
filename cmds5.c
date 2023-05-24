/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 06:33:10 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/16 06:33:11 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_pwd2(int pi)
{
	char	*pwd;
	int		save_out;

	pwd = getcwd(NULL, 0);
	if (pi == FPIPE || pi == PIPE)
	{	
		save_out = dup(fileno(stdout));
		dup2(g_fd[1], 1);
		printf ("%s\n", pwd);
		close(g_fd[1]);
		dup2(save_out, fileno(stdout));
	}
	else
		printf ("%s\n", pwd);
}

void	my_pwd(t_arg *cmd, int pi)
{
	char	*pwd;
	int		file_d;
	int		save_out;

	save_out = 0;
	file_d = 0;
	pwd = getcwd(NULL, 0);
	if (pi == PIPE || pi == EPIPE || pi == FPIPE)
		my_pwd2(pi);
	else if (pi == APND || pi == TRNC)
	{
		if (pi == APND)
			file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND);
		else
			file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC);
		save_out = dup(fileno(stdout));
		dup2(file_d, 1);
		ft_putstr_fd(pwd, file_d);
		dup2(save_out, fileno(stdout));
		close(file_d);
	}
	else
		printf ("%s\n", pwd);
}

void	my_exit(void)
{
	exit (printf("exit\n"));
}
