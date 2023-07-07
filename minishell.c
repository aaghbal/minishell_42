/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 02:47:50 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read(t_list **export_list, t_list *env_list)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	while (1)
	{
		signals();
		str = readline("\e[0;32mminishell ➜ \e[m");
		add_history(str);
		if (!str)
		{
			write(1, "exit\n", 6);
			exit(g_ext_s);
		}
		if (parsing(str))
		{
			if (str)
				free(str);
			continue ;
		}
		if (str)
			ft_reead_2(str, export_list, env_list, tmp);
	}
}

void	create_env(t_list **env_list, t_list **export_list)
{
	static int	i;

	i = 1;
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("PATH=", _PATH_STDPATH), 1));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0)), 1));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(i)), 1));
	ft_lstadd_back(env_list, ft_lstnew(ft_strjoin("_=", "usr/bin/env"), 1));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("PATH=", _PATH_STDPATH),
			1));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0)),
			1));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(i++)),
			1));
	ft_lstadd_back(export_list, ft_lstnew(ft_strjoin("_=", "usr/bin/env"), 1));
}

void	shelvl_env(t_list *env_list, char **env, int *i)
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
	ft_lstadd_back(&env_list, ft_lstnew(ft_strjoin("SHLVL=", s), 0));
	free(s);
	free(num);
}

void	ft_env_exp(char **env, t_list **env_list, t_list **export_list)
{
	int	i;

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
				ft_lstadd_back(env_list, ft_lstnew(env[i], 0));
		}
		i = -1;
		while (env[++i])
		{
			if (ft_strncmp(env[i], "SHLVL", 5) == 0)
				shelvl_env(*export_list, env, &i);
			else
				ft_lstadd_back(export_list, ft_lstnew(env[i], 0));
		}
	}
	ft_lstadd_front(export_list, ft_lstnew("__Head", 0));
	ft_lstadd_front(env_list, ft_lstnew("__Head", 0));
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
