/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:47 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/20 20:28:20 by aaghbal          ###   ########.fr       */
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
			free(tmp->content);
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
			free(tmp->content);
			free(tmp);
			tmp = NULL;
			break ;
		}
		env_list = tmp;
		tmp = tmp->next;
	}
	unset_export(cmd, export_list);
}

void	add_free(t_data *data, t_token **token, char *line)
{
	int i = 0;
	static int key = 0;
	if (key == 1)
	{
		ft_tokenadd_back(token, new_token(data->str, get_type(data->str), key));
		key = 0;
	}
	else
		ft_tokenadd_back(token, new_token(data->str, get_type(data->str), key));
	if (!ft_strncmp(data->str, "echo", 4) || get_token_pars(data->str))
	{
		i = data->i;
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == '\t')
				i++;
			else 
			{
				if (line[i] == '\"' || line[i] == '\"')
					key = 1;
				break ;
			}
		}
	}
	free(data->str);
	data->str= NULL;
}
void	is_token(t_data *data, char *line)
{
	data->str = get_token(&line[(data->i)++]);
	if (ft_strlen(data->str) == 2)
		(data->i)++;
}