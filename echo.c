/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:28 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:08:56 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	echo_newline(t_arg *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[++i])
	{
		if (!ft_strncmp(cmd->arg[i], "$?", 3))
			printf("%d", g_ext_s);
		else
			printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			printf(" ");
	}
	printf("\n");
}

int chek_arg(char *str)
{
	int j;

	j = 1;
	while (str[j])
	{
		if (str[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	my_echo(t_arg *cmd)
{
	int	i;

	if (cmd->arg[1][0] == '-' && cmd->arg[1][1] == 'n' && chek_arg(cmd->arg[1]))
	{
		i = 2;
		if (chek_arg(cmd->arg[i]))
			i++;
		while (cmd->arg[i])
		{
			if (!ft_strncmp(cmd->arg[i], "$?", 3))
				printf("%d", g_ext_s);
			else
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
