/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:33:39 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/20 17:59:05 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tabs(t_list *list)
{
	char	**tabs;
	t_list	*tmp;
	int		i;

	tabs = (char **)malloc((ft_lstsize(list) + 1) * sizeof(char *));
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
		exit (126);
	else
		exit (127);
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

void	signals(void)
{
	rl_catch_signals = 0;
	signal(3, sighandler);
	signal(11, sighandler);
	signal(2, sighandler);
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
