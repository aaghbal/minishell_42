/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 16:44:11 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_cd(t_arg *cmd)
{
	if (chdir(cmd->arg[1]) == -1)
	{
		printf ("cd: not a directory\n");
		g_ext_s = 1;
	}
}

void	my_env(t_list *env_list)
{
	while (env_list)
	{
		if (env_list->content)
			printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf ("%s\n", pwd);
}

void	my_exit(t_arg *cmd)
{
	printf("exit\n"); 
	if (cmd->arg[1])
		exit (ft_atoi(cmd->arg[1]));
	else
		exit (0);
}

void	my_echo(t_arg *cmd)
{
	int	i;

	if (!ft_strncmp(cmd->arg[1], "-n\0", 3))
	{
		i = 1;
		while (cmd->arg[++i])
		{
			if (!ft_strncmp(cmd->arg[i], "$?", 3))
				printf("%d", g_ext_s);
			else
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
			if (!ft_strncmp(cmd->arg[i], "$?", 3))
				printf("%d", g_ext_s);
			else
				printf("%s", cmd->arg[i]);
			if (cmd->arg[i + 1])
				printf(" ");
		}
		printf("\n");
	}
	g_ext_s = 0;
}
