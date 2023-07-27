/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/26 18:40:10 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_exp(t_list *exp, char *key)
{
	char	**tmp2;
	t_list	*head;

	head = exp;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(key, tmp2[0], ft_strlen(key)))
		{
			free(tmp2[0]);
			free(tmp2);
			return (tmp2[1]);
		}
		free_tabb(tmp2);
		head = head->next;
	}
	return (NULL);
}

void	my_cd2(t_arg *cmd, t_list *expo)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->arg[1])
	{
		if (chdir(cmd->arg[1]) == -1)
		{
			printf("cd: No such file or directory\n");
			g_ext_s = 1;
		}
	}
	else
	{
		tmp = get_key_exp((expo), "HOME");
		if (chdir(tmp) == -1)
		{
			printf("cd: HOME not set\n");
			g_ext_s = 1;
		}
		free(tmp);
	}
}

void	my_cd(t_arg *cmd, t_list *expo, t_list *env)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*buf;

	tmp = expo;
	tmp2 = env;
	ft_oldpwd(tmp);
	ft_oldpwd(tmp2);
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("cd: error retrieving current directory: getcwd: cannot parent\
 directories: No such file or directory\n");
		return ;
	}
	my_cd2(cmd, expo);
	tmp = expo;
	tmp2 = env;
	free(buf);
	ft_pwd(tmp);
	ft_pwd(tmp2);
}
