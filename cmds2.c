/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 16:43:39 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_epxport(t_list *export_list)
{
	while (export_list)
	{
		if (export_list->content)
			printf("declare -x %s\n", export_list->content);
		export_list = export_list->next;
	}
}

int	export_empty(t_list *export_list, t_list *env_list, char *var)
{
	int	i;

	i = 0;
	while (var[++i])
	{
		if (var[i] == '=' && var[i + 1] == '\0')
		{
			ft_lstadd_back(&export_list, ft_lstnew(ft_strjoin(var, "\"\"")));
			ft_lstadd_back(&env_list, ft_lstnew(ft_strjoin(var, "\"\"")));
			return (0);
		}
		else if (!var[i + 1])
			ft_lstadd_back(&export_list, ft_lstnew(var));
	}
	return (1);
}

void	my_export(t_list *export_list, t_list *env_list, char *var)
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
		if (!export_empty(export_list, env_list, var))
			return ;
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

void	unset_export(t_arg *cmd, t_list *export_list)
{
	t_list	*tmp;

	tmp = export_list;
	while (tmp)
	{
		if (!ft_strncmp(cmd->arg[1], tmp->content, ft_strlen(cmd->arg[1]))
			&& (!ft_strncmp(tmp->content + ft_strlen(cmd->arg[1]), "=", 1)
				|| !ft_strncmp(tmp->content + ft_strlen(cmd->arg[1]), "\0", 1)))
		{
			export_list->next = tmp->next;
			free(tmp);
			tmp = NULL;
			break ;
		}
		export_list = tmp;
		tmp = tmp->next;
	}
}

void	my_unset(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(cmd->arg[1], tmp->content, ft_strlen(cmd->arg[1]))
			&& !ft_strncmp(tmp->content + ft_strlen(cmd->arg[1]), "=", 1))
		{
			env_list->next = tmp->next;
			free(tmp);
			tmp = NULL;
			break ;
		}
		env_list = tmp;
		tmp = tmp->next;
	}
	unset_export(cmd, export_list);
}
