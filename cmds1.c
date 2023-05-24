/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:51:54 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_cd(t_arg *cmd)
{
	chdir(cmd->arg[1]);
}

void	my_env(t_list *env_list, int pi)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void	print_epxport(t_list *export_list)
{
	while (export_list)
	{
		printf("declare -x %s\n", export_list->content);
		export_list = export_list->next;
	}
}

void	my_export(t_list *export_list, t_list *env_list, char *var, int pi)
{
	int	i;

	i = 0;
	if (var)
	{
		if (var[0] == '=')
		{
			printf("\e[0;31mnot a valid identifier\n");
			return ;
		}
		ft_lstadd_back(&export_list, ft_lstnew(var));
		while (var[++i])
		{
			if (var[i] == '=' && var[i - 1] != ' '
				&& var[i + 1] != ' ' && var[i + 1] != '\0')
			{
				ft_lstadd_back(&env_list, ft_lstnew(var));
				return ;
			}
		}
		return ;
	}
	print_epxport(export_list);
}

//???????????????
void	my_unset(t_list *env_list)
{
	printf("%s\n", env_list->content);
}
