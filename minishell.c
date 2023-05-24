/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:59 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list, int pi)
{
	if (!ft_strncmp(cmd->cmd, "pwd\0", 4))
		my_pwd(cmd, pi);
	else if (!ft_strncmp(cmd->cmd, "exit\0", 5))
		my_exit();
	else if (!ft_strncmp(cmd->cmd, "echo\0", 5))
		my_echo(cmd, pi);
	else if (!ft_strncmp(cmd->cmd, "cd\0", 3))
		my_cd(cmd);
	else if (!ft_strncmp(cmd->cmd, "env\0", 4))
		my_env(env_list, pi);
	else if (!ft_strncmp(cmd->cmd, "export\0", 6))
		my_export(export_list, env_list, cmd->arg[1], pi);
	else if (!ft_strncmp(cmd->cmd, "unset\0", 6))
		my_unset(env_list);
	else
		my_exec_cmd(cmd, pi);
}

int	main(int ac, char **av, char *env[])
{
	t_list	*env_list;
	t_list	*export_list;
	char	*str;
	int		i;
	char	*tmp;

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
	while (1)
	{
		str = readline("\e[0;32mminishell ➜ \e[m");
		if (str)
		{
			add_history(str);
			tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
			ft_strlcpy(tmp, str, ft_strlen(str) + 1);
			if (ft_parsing(tmp) == 0 || token_line(str, export_list, env_list) ==  0)
			{
				write(1, "syntax error\n", 13);
				continue;
			}
			free(str);
		}
	}
}
	//if there is are no pipe execute all_cmds normally
	//if next node is a pipe change output to stdin and read from pipe
	//if next node is a and before is a pipe read from pipe and output normaly to stdoutuse all_cmd2
