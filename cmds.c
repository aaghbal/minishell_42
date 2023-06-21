/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/21 03:11:41 by aaghbal          ###   ########.fr       */
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
		tmp2 = ft_split(head ->content, '=');
		if (!ft_strncmp(key, tmp2[0], ft_strlen(key)))
			return (tmp2[1]);
		free_tabb(tmp2);
		head = head->next;
	}
	return (NULL);
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
	tmp = expo;
	tmp2 = env;
	ft_pwd(tmp);
	ft_pwd(tmp2);
}

void	my_env(t_list *env_list)
{
	while (env_list)
	{
		if (env_list->content)
			printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

void	my_pwd(t_list *export_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s\n", get_key_exp(export_list, "PWD"));
		return ;
	}
	printf("%s\n", pwd);
}

void	my_exit(t_arg *cmd)
{
	printf("exit\n");
	if (cmd->arg[1])
		exit(ft_atoi(cmd->arg[1]));
	else
		exit(0);
}
