/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:08:39 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_pwd(t_list **expo)
{
	char 	**tmp2;
	t_list *head = *expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(tmp2[0], "PWD", ft_strlen(tmp2[0])) && ft_strlen(tmp2[0]) == ft_strlen("PWD"))
		{
			head->content = ft_substr(head->content, 0, ft_strlen("PWD="));
			head->content = ft_strjoin(head->content, getcwd(NULL, 0));
		}
		free_tabb(tmp2);
		head = head->next;
	}
}
void	ft_oldpwd(t_list **expo)
{
	char 	**tmp2;
	t_list *head = *expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(tmp2[0], "OLDPWD", ft_strlen(tmp2[0])) && ft_strlen(tmp2[0]) == ft_strlen("OLDPWD"))
		{
			head->content = ft_substr(head->content, 0, ft_strlen("OLDPWD="));
			head->content = ft_strjoin(head->content, getcwd(NULL, 0));
		}
		free_tabb(tmp2);
		head = head->next;
	}
}

void	my_cd(t_arg *cmd, t_list **expo)
{
	ft_oldpwd(expo);
	if (chdir(cmd->arg[1]) == -1)
	{
		printf ("cd: not a directory\n");
		g_ext_s = 1;
	}
	ft_pwd(expo);
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

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf ("%s\n", pwd);
}

void	my_exit(t_arg *cmd)
{
	printf("exit\n");
	if (cmd->arg[1])
		exit (ft_atoi(cmd->arg[1]));
	else
		exit (0);
}