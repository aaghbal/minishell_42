/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/02 22:40:06 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_epxport(t_list *export_list)
{
	char	*tmp;
	int		i;

	if (!ft_strncmp("__Head", export_list->content, 7))
		export_list = export_list->next;
	while (export_list)
	{
		printf("declare -x ");
		tmp = ft_strdup(export_list->content);
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '=')
			{
				printf("=\"");
				printf("%s", ft_strchr(export_list->content, '=') + 1);
				printf("\"");
				break ;
			}
			printf("%c", tmp[i]);
		}
		printf("\n");
		free(tmp);
		export_list = export_list->next;
	}
}

void	export_empty(t_list *export_list, t_list *env_list, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(var);
	while (var[++i])
	{
		if (var[i] == '=')
		{
			ft_lstadd_back(&export_list, ft_lstnew(tmp, 1));
			ft_lstadd_back(&env_list, ft_lstnew(tmp, 1));
			return ;
		}
		else if (!var[i + 1])
			ft_lstadd_back(&export_list, ft_lstnew(tmp, 1));
	}
	return ;
}

char	*add_var(t_list *export_list, char *var)
{
	char	**tmp2;
	char	**tmp3;
	char	*tmp;

	tmp3 = ft_split(var, '+');
	while (export_list)
	{
		tmp2 = ft_split(export_list->content, '=');
		if (!ft_strncmp(tmp2[0], tmp3[0], ft_strlen(tmp3[0]))
			&& ft_strlen(tmp3[0]) == ft_strlen(tmp2[0]))
		{
			if (tmp3[1] && tmp3[1][1] != '\0')
			{
				var = ft_strjoin(export_list->content, tmp3[1] + 1);
				return (free_tabb(tmp2), free_tabb(tmp3), var);
			}
			tmp = ft_strjoin(tmp3[0], tmp3[1]);
			return (free_tabb(tmp2), free_tabb(tmp3), tmp);
		}
		free_tabb(tmp2);
		export_list = export_list->next;
	}
	tmp = ft_strjoin(tmp3[0], tmp3[1]);
	free_tabb(tmp3);
	return (tmp);
}

int	same_var(t_list *export_list, t_list *env_list, char *var)
{
	t_list	*tmp;
	char	**tmp2;
	char	**tmp3;

	tmp = export_list;
	tmp3 = ft_split(var, '=');
	while (tmp)
	{
		tmp2 = ft_split(tmp->content, '=');
		if (!ft_strncmp(tmp2[0], tmp3[0], ft_strlen(tmp3[0]))
			&& ft_strlen(tmp3[0]) == ft_strlen(tmp2[0]))
		{
			if (!tmp3[1] && var[ft_strlen(var) - 1] != '=')
				return (free_tabb(tmp2), free_tabb(tmp3), 0);
			my_unset(tmp2[0], export_list, env_list);
			return (free_tabb(tmp2), free_tabb(tmp3), 1);
		}
		free_tabb(tmp2);
		tmp = tmp->next;
	}
	return (free_tabb(tmp3), 1);
}

void	my_export(t_list *export_list, t_list *env_list, char *var)
{
	char	*tmp;

	if (var)
	{
		tmp = ft_strdup(export_pars(export_list, var));
		if (!tmp)
			return ;
		if (!same_var(export_list, env_list, tmp))
			return ;
		export_empty(export_list, env_list, tmp);
		if (var != tmp)
			free (tmp);
		return ;
	}
	else
		print_epxport(export_list);
}
