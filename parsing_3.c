/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:11:12 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/05 19:40:41 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_arg *cmd, t_list *list_env, char **str)
{
	char	**env;
	int		i;

	i = 0;
	env = list_to_tabs(list_env);
	execve(cmd->cmd, cmd->arg, env);
	while (str && str[i])
	{
		if (execve(ft_strjoin(str[i], cmd->cmd), cmd->arg, env) == -1)
			i++;
	}
}

void	ft_exu_other(t_arg *cmd, t_list *export_list, t_list *list_env)
{
	char	**str;
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
	ft_exec(cmd, list_env, str);
	exit(127);
}

void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "\t", 3))
		exit(0);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		my_pwd(export_list);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		my_exit(cmd);
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		my_echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		my_cd(cmd, export_list, env_list);
	else if (!ft_strncmp(cmd->cmd, "env", 4) && !cmd->arg[1])
		my_env(env_list);
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		my_export(export_list, env_list, cmd->arg[1]);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		my_unset(cmd->arg[1], export_list, env_list);
	else
		ft_exu_other(cmd, export_list, env_list);
	exit(0);
}

void	ft_reead_2(char *str, t_list **export_list, t_list *env_list, char *tmp)
{
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		exit(0);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	if (ft_parsing(tmp) || token_line(str, *export_list, env_list))
	{
		printf("\e[0;31msyntax error\n");
		g_ext_s = 258;
	}
}

void	default_cmd(t_data *data, char *line, t_list *expo)
{
	while (line[(data->i)] && !is_char(line[data->i]))
	{
		if (line[data->i] == '$' && (ft_isalpha(line[data->i + 1])
				|| line[data->i + 1] == '_' || line[data->i + 1] == '?'))
		{
			data->str = ft_expand(line, &data->i, data->str, expo);
			if (line[data->i] == '?')
				data->i++;
		}
		else if (line[(data->i)] != '\"' && line[data->i] != '\''
			&& line[(data->i)])
			data->str = append_char(data->str, line[(data->i)++]);
		else
		{
			if (line[(data->i)] == '\"')
				data->str = double_quotes(line, data->str, &(data->i), expo);
			else if (line[data->i] == '\'')
				data->str = single_quotes(line, data->str, &(data->i));
		}
	}
}
