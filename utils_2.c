/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:33:39 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/25 14:06:52 by aaghbal          ###   ########.fr       */
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
		g_ext_s = 258;
		return (1);
	}
	return (0);
}
