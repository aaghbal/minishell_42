/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:47 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:09:13 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	unset_export(char *cmd, t_list *export_list)
{
	t_list	*tmp;

	tmp = export_list;
	while (tmp)
	{
		if (!ft_strncmp(cmd, tmp->content, ft_strlen(cmd))
			&& (!ft_strncmp(tmp->content + ft_strlen(cmd), "=", 1)
				|| !ft_strncmp(tmp->content + ft_strlen(cmd), "\0", 1)))
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

void	my_unset(char *cmd, t_list *export_list, t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(cmd, tmp->content, ft_strlen(cmd))
			&& !ft_strncmp(tmp->content + ft_strlen(cmd), "=", 1))
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
