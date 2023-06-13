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

void	ft_exu_other(t_arg *cmd, t_list *export_list)
{
	char **str;
	int i;

	i = 0;
	while (export_list)
	{
		if (!ft_strncmp(export_list->content, "PATH", 4))
			break;
		export_list = export_list->next;
	}
	str = ft_split(export_list->content, '=');
	str = ft_split(str[1], ':');
	while (str[i])
	{
		str[i] = ft_strjoin(str[i], "/");
		i++;
	}
	i = 0;	
	while (str[i])
	{
		if (execve(ft_strjoin(str[i], cmd->cmd), cmd->arg, NULL) == -1)
			i++;
	}
	printf("\e[0;31mminishell: command not found\n");

}

void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "pwd", 4))
		my_pwd();
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		my_exit(cmd);
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		my_echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		my_cd(cmd);
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		my_env(env_list);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		my_export(export_list, env_list, cmd->arg[1]);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		my_unset(cmd, export_list, env_list);
	else
		ft_exu_other(cmd ,export_list);
	exit (0);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_line_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\"'
			&& str[i] != '\'' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	ft_read(t_list	*export_list, t_list *env_list)
{
	char	*tmp;
	char	*str;

	while (1)
	{
		rl_catch_signals = 0;
		str = readline("\e[0;32mminishell ➜ \e[m");
		if (parsing(str))
			continue ;
		add_history(str);
		if (str)
		{
			tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
			ft_strlcpy(tmp, str, ft_strlen(str) + 1);
			if (ft_parsing(tmp) || token_line(str, export_list, env_list))
			{
				printf("\e[0;31msyntax error\n");
				g_ext_s = 258;
				continue ;
			}
			free(str);
		}
	}
}

int	main(int ac, char **av, char *env[])
{
	t_list	*env_list;
	t_list	*export_list;
	char	*str;
	int		i;

	(void)av;
	(void)ac;
	str = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_back(&env_list, ft_lstnew(env[i]));
	i = -1;
	while (env[++i])
		ft_lstadd_back(&export_list, ft_lstnew(env[i]));
	i = -1;
	signal(2, sighandler);
	signal(3, sighandler);
	signal(11, sighandler);
	ft_read(export_list, env_list);
}
