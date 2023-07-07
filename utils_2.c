/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:33:39 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/07 09:05:49 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tabs(t_list *list)
{
	char	**tabs;
	t_list	*tmp;
	int		i;

	tabs = (char **)malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (!tabs)
		exit(0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		tabs[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	tabs[i] = NULL;
	return (tabs);
}

void	ft_error(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		exit(126);
	else
		exit(127);
}

void	ft_execve(char **str, t_arg *cmd, char **env)
{
	int	i;

	i = 0;
	execve(cmd->cmd, cmd->arg, env);
	while (str && str[i])
	{
		if (execve(ft_strjoin(str[i], cmd->cmd), cmd->arg, env) == -1)
			i++;
	}
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	parsing(char *str)
{
	if (check_line(str))
		return (1);
	if (check_line_2(str))
	{
		printf("\e[0;31msyntax error\n");
		g_ext_s = 127;
		return (1);
	}
	return (0);
}
