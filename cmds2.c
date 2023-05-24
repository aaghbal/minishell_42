/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:51:59 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_echo1(t_arg *cmd, int pi)
{
	int	file_d;
	int	save_out;

	save_out = 0;
	file_d = 0;
	if (pi == APND)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	ft_putendl_fd("", file_d);
	dup2(save_out, fileno(stdout));
	close(file_d);
}

void	my_echo2(t_arg *cmd, int pi)
{
	int	file_d;
	int	save_out;
	int	i;

	save_out = 0;
	file_d = 0;
	if (pi == APND)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	{			
		i = 1;
		while (cmd->arg[i])
		{
			ft_putstr_fd(cmd->arg[i], file_d);
			if (cmd->arg[i + 1])
				ft_putstr_fd(" ", file_d);
			i++;
		}
		ft_putstr_fd("\n", file_d);
	}
	dup2(save_out, fileno(stdout));
	close(file_d);
}

void	my_echo3(t_arg *cmd, int pi)
{
	int	file_d;
	int	save_out;
	int	i;

	save_out = 0;
	file_d = 0;
	if (pi == APND)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	i = 2;
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], file_d);
		if (cmd->arg[i + 1])
			ft_putstr_fd(" ", file_d);
		i++;
	}
	dup2(save_out, fileno(stdout));
	close(file_d);
}

void	my_echo4(t_arg *cmd)
{
	int	i;

	if (!ft_strncmp(cmd->arg[1], "-n\0", 3))
	{
		i = 1;
		while (cmd->arg[++i])
		{
			printf("%s", cmd->arg[i]);
			if (cmd->arg[i + 1])
				printf(" ");
		}
	}
	else
	{
		i = 0;
		while (cmd->arg[++i])
		{
			printf("%s", cmd->arg[i]);
			if (cmd->arg[i + 1])
				printf(" ");
		}
		printf("\n");
	}
}

void	my_echo(t_arg *cmd, int pi)
{
	if (pi == NOR)
		my_echo4(cmd);
	else if (pi == APND || pi == TRNC)
	{
		if (!cmd->arg[1])
			my_echo1(cmd, pi);
		else
		{
			if (!ft_strncmp(cmd->arg[1], "-n\0", 3))
				my_echo3(cmd, pi);
			else
				my_echo2(cmd, pi);
		}
	}
	// else if (pi == PIPE)
}
