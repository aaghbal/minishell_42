/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:02 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/09 13:10:04 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_pip(t_arg *arg)
{
	int c;

	c = 0;
	while (arg)
	{
		if (arg->cmd[0] == '|')
			c++;
		arg = arg->next;
	}
	return(c);
}

int	get_next_red(t_arg *arg)
{
	int c;

	c = 0;
	while (arg)
	{
		if (arg->cmd[0] == '>' || arg->cmd[0] == '<')
			c++;
		arg = arg->next;
	}
	return(c);
}

t_token * new_token(char *cmd, t_type type)
{
	t_token * node;

	if (type == NONE)
		return (NULL);
	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	node->type = type;
	node->next = NULL;
	return (node);
}


int is_char(char c)
{
	if (c == ' ' || c == '\t' || check_token(c))
		return (1);
	return(0);
}

char *get_token(char *line)
{
	int i;
	
	if (!line)
		return (NULL);
	i = 0;
	if (line[i] && (line[i] == '|' || line[i] == '<' || line[i] == '>') 
		&& (line[i + 1] != '<' && line[i + 1] != '>'))
		return ft_substr(line, 0, 1);
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<')
	|| (line[i] == '>' && line[i + 1] == '>')))
		return ft_substr(line, 0, 2);
	return NULL;
}

void	is_token(t_data *data, char *line)
{
	data->str = get_token(&line[(data->i)++]);
		if (ft_strlen(data->str) == 2)
			(data->i)++;
}

int  token_line(char *line, t_list *export_list, t_list *env_list)
{
	t_data *data;
	t_arg *arg;
	t_token	*token;

	data = malloc(sizeof(t_data));
	arg = NULL;
	token = NULL;
	data->i = 0;
	data->str = NULL;
	while (line[data->i])
	{
		while (line[(data->i)] == ' ' || line[(data->i)] == '\t')
			(data->i)++;
		if (check_token(line[data->i]))
			is_token(data, line);
		else if (line[data->i] == '\"')
			data->str = double_quotes(line, data->str, &(data->i));
		else if (line[data->i] == '\'')
			data->str = single_quotes(line, data->str, &(data->i));
		else
			default_cmd(data, line);
		if (data->str)
			add_free(data, &token);
	}
	if (ft_parsing_2(&token) == 0)
	{
		free_list(token);
		return(0);
	}
	is_arg(token, &arg);
	int num_pipes = 0;
	t_arg *tmp = arg;
	get_next_pip(arg);
	if (get_next_pip(arg) == 0)
		all_cmd(arg, export_list, env_list, NOR);
	else
	{
		int fd[2];
		int s = 0;
		while (tmp)
		{
			if (tmp->cmd[0] == '|')
				tmp = tmp->next;
			pipe(fd); // fd[0] fd[1]
			int pid = fork();
			if (pid == 0)
			{
				if (tmp->next && tmp->next->cmd[0] == '>')
				{

				}
				else if (tmp->next && tmp->next->cmd[0] == '|')
				{
					dup2(fd[1], 1);
				}
				if (s > 0)
				{
					dup2(s, 0);
					close(s);
				}
				close(fd[1]);
				close(fd[0]);
				if (execve (tmp->cmd , tmp->arg,  NULL) == -1)
				if (execve (ft_strjoin("/bin/", tmp->cmd ),tmp->arg, NULL) == -1)
				if (execve (ft_strjoin("/usr/bin/", tmp->cmd ),tmp->arg, NULL) == -1)
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
			}
			else
			{
				if (s > 0)
					close(s);
				s = dup(fd[0]);
				close(fd[1]);
				close(fd[0]);
			}
			tmp = tmp->next;
		}
		while (wait(0) != -1 || errno != ECHILD);
	}
}

	// while (arg)
	// {

	// }
	
	// // while(arg->next)
	// {
	// 	if(arg->cmd[0] == '|')
	// 		num_pipes++;
	// 	arg = arg->next;
	// }
	// arg = tmp;
	// while(arg)
	// {
	// 	if (arg->cmd[0] == '>' || arg->cmd[0] == '|')
	// 		arg = arg->next;
	// 	else if (arg->next && arg->next->arg[0][0] == '|')
	// 	{
	// 		//only redirect output to fd[1]
	// 		arg->t_pipes = num_pipes;
	// 		while (num_pipes >= 0)
	// 		{
	// 			pipe(g_fd[num_pipes]);
	// 			num_pipes--;
	// 		}
	// 		all_cmd(arg, export_list, env_list, FPIPE);
	// 		arg = arg->next;
	// 		while (arg)
	// 		{
	// 			if (arg->next)
	// 				arg->next->t_pipes = arg->t_pipes;
	// 			if (arg->cmd[0] == '|' || arg->cmd[0] == '>')
	// 				arg = arg->next;
	// 			else if (arg->next && arg->next->arg[0][0] == '>')
	// 			{
	// 				if (arg->next->arg[0][1] == '\0')
	// 					all_cmd(arg, export_list, env_list, TRNC);
	// 				else
	// 					all_cmd(arg, export_list, env_list, APND);
	// 				arg = arg->next;
	// 			}
	// 			else if (!arg->next)
	// 			{
	// 				//read from fd[0] and output normaly
	// 				all_cmd(arg, export_list, env_list, EPIPE);
	// 				arg = arg->next;
	// 			}
	// 			else
	// 			{
	// 				//redirect output to stdin and read from fd[0]
	// 				all_cmd(arg, export_list, env_list, PIPE);
	// 				arg = arg->next;
	// 			}
	// 		}
	// 	}
	// 	else if (arg->next && arg->next->arg[0][0] == '>')
	// 	{
	// 		if (arg->next->arg[0][1] == '\0')
	// 			all_cmd(arg, export_list, env_list, TRNC);
	// 		else
	// 			all_cmd(arg, export_list, env_list, APND);
	// 		arg = arg->next;
	// 	}
	// 	else
	// 	{
	// 		all_cmd(arg, export_list, env_list, NOR);
	// 		arg = arg->next;
	// 	}
	// }
