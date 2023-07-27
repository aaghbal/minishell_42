/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:28:26 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/03 16:45:30 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_env(t_list *env_list)
{
	if (!ft_strncmp("__Head", env_list->content, 7))
		env_list = env_list->next;
	while (env_list)
	{
		if (env_list->content)
			printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void	my_pwd(t_list *export_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s\n", get_key_exp(export_list, "PWD"));
		return ;
	}
	printf("%s\n", pwd);
}

t_arg	*my_exit(t_arg *cmd)
{
	int	i;

	i = -1;
	if (cmd->arg[1])
	{
		while (cmd->arg[1][++i])
		{
			if (!ft_isdigit(cmd->arg[1][i]))
			{
				printf("exit\nminishell: exit: numeric argument required\n");
				exit (255);
			}
		}
		if (cmd->arg[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			g_ext_s = 1;
			cmd = cmd->next;
		}
		else
			exit (ft_atoi(cmd->arg[1]));
	}
	else
		exit(0);
	return (cmd);
}
