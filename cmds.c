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
	char 	*tmp;
	char	*tmp3;
	t_list *head = *expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(tmp2[0], "PWD", ft_strlen(tmp2[0])) && ft_strlen(tmp2[0]) == ft_strlen("PWD"))
		{
			tmp = ft_substr(head->content, 0, ft_strlen("PWD="));
            tmp3 = ft_strjoin(tmp, getcwd(NULL, 0));
            head->content = tmp3;
            free(tmp);
		}
		free_tabb(tmp2);
		head = head->next;
	}
}
void	ft_oldpwd(t_list **expo)
{
	char 	**tmp2;
	char 	*tmp;
	char 	*tmp3;
	t_list *head = *expo;
	while (head)
	{
		tmp2 = ft_split(head->content, '=');
		if (!ft_strncmp(tmp2[0], "OLDPWD", ft_strlen(tmp2[0])) && ft_strlen(tmp2[0]) == ft_strlen("OLDPWD"))
		{
			tmp = ft_substr(head->content, 0, ft_strlen("OLDPWD="));
            tmp3 = ft_strjoin(tmp, getcwd(NULL, 0));
            head->content = tmp3;
            free(tmp);
		}
		free_tabb(tmp2);
		head = head->next;
	}
}

char *get_key_exp(t_list *exp, char *key)
{
	char **tmp2;

	while (exp)
	{
		tmp2 = ft_split(exp->content, '=');
		if (!ft_strncmp(key, tmp2[0], ft_strlen(key)))
			return tmp2[1];
		free_tabb(tmp2);
		exp = exp->next;
	}
	return (NULL);
}

void	my_cd(t_arg *cmd, t_list **expo, t_list  **env)
{
	t_list *tmp = *expo;
	t_list *tmp2 = *env;
	ft_oldpwd(&tmp);
	ft_oldpwd(&tmp2);
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
		if (chdir(get_key_exp((*expo), "HOME")) == -1)
		{
			printf("cd: HOME not set\n");
			g_ext_s = 1;
		}

	}
	g_ext_s = 0;
	tmp = *expo;
	tmp2 = *env;
	ft_pwd(&tmp);
	ft_pwd(&tmp2);
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