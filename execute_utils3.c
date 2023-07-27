/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:13:25 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/02 10:13:26 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_cmd_inpt(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = -1;
	if (tmp->next && tmp->next->arg[1])
	{
		tmp->next->cmd = ft_strdup(tmp->next->arg[1]);
		while (tmp->next->arg[++i])
			tmp->next->arg[i] = tmp->next->arg[i + 1];
		all_cmd(tmp->next, export_list, env_list);
	}
	else
		exit (0);
}

void	close_file(int file_d, int fd[2])
{
	if (file_d)
		close(file_d);
	close(fd[1]);
	close(fd[0]);
}

t_arg	*if_unset(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = 0;
	if (tmp->next && tmp->next->cmd[0] == '|')
		tmp = tmp->next;
	else
	{
		while (tmp->arg[++i])
			my_unset(tmp->arg[i], env_list, export_list);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}
