/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:49 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/08 11:43:22 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_addpars(t_list *export_list, char *var, int i)
{
	if (var[i + 1] && var[i + 1] == '=' && ft_isalnum(var[i - 1]))
		return (add_var(export_list, var));
	else
	{
		printf ("export: %s: not a valid identifier\n", var);
		return (NULL);
	}
}

char	*export_pars(t_list *export_list, char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
	{
		printf("\e[0;31mminishell: export: not a valid identifier\n");
		g_ext_s = 1;
		return (NULL);
	}
	while (var[++i])
	{
		if (var[i] == '=')
		{
			if (!ft_isalnum(var[i - 1]))
			{
				printf ("export: %s: not a valid identifier\n", var);
				return (NULL);
			}
			else
				break ;
		}
		if (var[i] == '+')
			return (export_addpars(export_list, var, i));
	}
	return (var);
}

t_list	*sort_export(t_list	*export_list)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*tmp3;

	tmp = export_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->content, tmp2->content,
					ft_strlen(tmp->content)) > 0)
			{
				tmp3 = tmp->content;
				tmp->content = tmp2->content;
				tmp2->content = tmp3;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (export_list);
}
