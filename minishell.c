/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 18:32:20 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "pwd\0", 4))
		my_pwd();
	else if (!ft_strncmp(cmd->cmd, "exit\0", 5))
		my_exit();
	else if (!ft_strncmp(cmd->cmd, "echo\0", 5))
		my_echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "cd\0", 3))
		my_cd(cmd);
	else if (!ft_strncmp(cmd->cmd, "env\0", 4))
		my_env(env_list);
	else if (!ft_strncmp(cmd->cmd, "export\0", 6))
		my_export(export_list, env_list, cmd->arg[1]);
	else if (!ft_strncmp(cmd->cmd, "unset\0", 6))
		my_unset(cmd, export_list, env_list);
	else
	{
		if (execve(cmd->cmd, cmd->arg, NULL) == -1)
			if (execve(ft_strjoin("/bin/", cmd->cmd), cmd->arg, NULL) == -1)
				if (execve(ft_strjoin("/usr/bin/", cmd->cmd), cmd->arg, NULL)
					== -1)
					printf("\e[0;31mminishell: command not found\n");
	}
	exit (0);
}

int	check_line(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return(0);
		i++;
	}
	return(1);
}
int	check_line_2(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\"'
			&& str[i] != '\'' && str[i] != '\t')
			return(0);
		i++;
	}
	return(1);
}

int	parsing(char *str)
{
	if (check_line(str))
			return (1);
	if (check_line_2(str))
	{
		free(str);
		printf("\e[0;31mminishell : command not found\n");
		return (1);
	}
	return (0);
}

void	ft_read(t_list	*export_list, t_list *env_list)
{
	char	*tmp;
	char *str;

	while (1)
	{
		str = readline("\e[0;32mminishell ➜ \e[m");
		if (parsing(str))
			continue;
		add_history(str);
		if (str)
		{
			tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
			ft_strlcpy(tmp, str, ft_strlen(str) + 1);
			if (ft_parsing(tmp) || token_line(str, export_list, env_list))
			{
				printf("\e[0;31msyntax error\n");
				continue;
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
	ft_read(export_list, env_list);
}

