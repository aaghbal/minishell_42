/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/03 15:47:18 by zel-kach         ###   ########.fr       */
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
			return (tmp2[1]);
		free_tabb(tmp2);
		head = head->next;
	}
	return (NULL);
}

void	my_cd2(t_arg *cmd, t_list *expo)
{
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
		if (chdir(get_key_exp((expo), "HOME")) == -1)
		{
			printf("cd: HOME not set\n");
			g_ext_s = 1;
		}
	}
}

void	my_cd(t_arg *cmd, t_list *expo, t_list *env)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = expo;
	tmp2 = env;
	ft_oldpwd(tmp);
	ft_oldpwd(tmp2);
	if (!getcwd(NULL, 0))
	{
		printf("cd: error retrieving current directory: getcwd: cannot parent\
 directories: No such file or directory\n");
		return ;
	}
	my_cd2(cmd, expo);
	tmp = expo;
	tmp2 = env;
	ft_pwd(tmp);
	ft_pwd(tmp2);
}
