/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:28 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/05 19:28:24 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_newline(t_arg *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[++i])
	{
		printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			printf(" ");
	}
	printf("\n");
}

int	chek_arg(char *str)
{
	int	j;

	j = 0;
	if (str[0] == '-')
	{
		j++;
		while (str[j])
		{
			if (str[j] == 'n')
				j++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	my_echo(t_arg *cmd)
{
	int	i;

	if (cmd->arg[1] && cmd->arg[1][0] == '-' && cmd->arg[1][1] == 'n'
		&& chek_arg(cmd->arg[1]))
	{
		i = 1;
		while (cmd->arg[i] && chek_arg(cmd->arg[i]))
			i++;
		while (cmd->arg[i])
		{
			if (!ft_strncmp(cmd->arg[i], "$?", 3))
				printf("%d", g_ext_s);
			printf("%s", cmd->arg[i]);
			if (cmd->arg[i + 1])
				printf(" ");
			i++;
		}
	}
	else
		echo_newline(cmd);
	g_ext_s = 0;
}
