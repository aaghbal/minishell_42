/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/13 13:48:26 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exu_other(t_arg *cmd, t_list *export_list, t_list *list_env)
{
	char	**str;
	char	**env;
	int		i;

	i = 0;
	str = NULL;
	while (export_list)
	{
		if (!ft_strncmp(export_list->content, "PATH", 4))
			break ;
		export_list = export_list->next;
	}
	if (export_list && !ft_strncmp(export_list->content, "PATH", 4))
	{
		str = ft_split(export_list->content, '=');
		str = ft_split(str[1], ':');
	}
	while (str && str[i])
	{
		str[i] = ft_strjoin(str[i], "/");
		i++;
	}
	i = 0;
	env = list_to_tabs(list_env);
	execve(cmd->cmd, cmd->arg, env);
	while (str && str[i])
	{
		if (execve(ft_strjoin(str[i], cmd->cmd), cmd->arg, env) == -1)
			i++;
	}
	exit (127);
}

void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "\t", 3))
		exit (0);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		my_pwd(export_list);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		my_exit(cmd);
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		my_echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		my_cd(cmd, export_list, env_list);
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		my_env(env_list);
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		my_export(export_list, env_list, cmd->arg[1]);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		my_unset(cmd->arg[1], export_list, env_list);
	else
		ft_exu_other(cmd, export_list, env_list);
	exit (0);
}


void	ft_read(t_list	**export_list, t_list *env_list)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	while (1)
	{
		rl_catch_signals = 0;
		signal(3, sighandler);
		signal(11, sighandler);
		signal(2, sighandler);
		str = readline("\e[0;32mminishell ➜ \e[m");
		add_history(str);
		if (parsing(str))
		{
			if (str)
				free(str);
			continue ;
		}
		if (str)
		{
			tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
			if (!tmp)
				return ;
			ft_strlcpy(tmp, str, ft_strlen(str) + 1);
			if (ft_parsing(tmp) || token_line(str, *export_list, env_list))
			{
				printf("\e[0;31msyntax error\n");
				g_ext_s = 258;
			}
		}
	}
	system("leaks minishell");
}

void	create_env(t_list **env_list, t_list **export_list)
{
	static int i = 1;
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("PATH=", _PATH_STDPATH)));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0))));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(i))));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("_=", "usr/bin/env")));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("PATH=", _PATH_STDPATH)));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0))));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(i++))));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("_=", "usr/bin/env")));
}


void	shelvl_env(t_list	*env_list, char **env , int *i)
{
	int		a;
	char	*num;
	char	*s;
	num = ft_substr(env[*i], 6, ft_strlen(env[*i]));
	a = ft_atoi(num);
	if (a < 0)
		a = -1;
	a++;
	s = ft_itoa(a);
	ft_lstadd_back(&env_list, ft_lstnew(ft_strjoin("SHLVL=", s)));
	free(s);
	free(num);
}

void	ft_env_exp(char **env, t_list	**env_list, t_list	**export_list)
{
	int		i;

	i = -1;
	if (!env[0])
		create_env(env_list, export_list);
	else
	{
		while (env[++i])
		{
			if (ft_strncmp(env[i], "SHLVL", 5) == 0)
				shelvl_env(*env_list, env, &i);
			else
				ft_lstadd_back(env_list, ft_lstnew(env[i]));
		}
		i = -1;
		while (env[++i])
		{
			if (ft_strncmp(env[i], "SHLVL", 5) == 0)
				shelvl_env(*export_list, env, &i);
			else
				ft_lstadd_back(export_list, ft_lstnew(env[i]));
		}
	}
}

int	main(int ac, char **av, char *env[])
{
	t_list	*env_list;
	t_list	*export_list;

	env_list = NULL;
	export_list = NULL;
	(void)av;
	(void)ac;
	ft_env_exp(env, &env_list, &export_list);
	ft_read(&export_list, env_list);
}
