/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 11:47:01 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_arg *tmp)
{
	int	file_d;

	if (tmp->next->cmd[1] == '\0')
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(file_d, STDOUT_FILENO);
	return (file_d);
}

int	redirect2(t_arg *tmp)
{
	int	file_d;

	file_d = 0;
	if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, ">>", 3))
	{
		file_d = open(tmp->next->next->redfile, O_CREAT
				| O_RDWR | O_APPEND, 0644);
		dup2(file_d, STDOUT_FILENO);
	}
	else if (tmp->next->next && !ft_strncmp(tmp->next->next->cmd, ">", 2))
	{
		file_d = open(tmp->next->next->redfile, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
		dup2(file_d, STDOUT_FILENO);
	}
	return (file_d);
}

void	multi_red(t_arg *tmp)
{
	t_arg	*tmp2;
	int		file_d;

	file_d = 0;
	tmp2 = tmp;
	while (tmp2->next && tmp2->next->cmd[0] == '>')
	{
		if (tmp2->next->cmd[1] == '>')
			file_d = open(tmp2->next->redfile, O_CREAT | O_RDWR
					| O_APPEND, 0644);
		else
			file_d = open(tmp2->next->redfile, O_CREAT | O_RDWR
					| O_TRUNC, 0644);
		close(file_d);
		tmp2 = tmp2->next;
	}
}

int	redirect_inpt(t_arg *tmp, int fd[2])
{
	int	file_d;

	if (tmp->next && !ft_strncmp(tmp->next->cmd, ">", 2))
		tmp = tmp->next;
	if (tmp->next && !access(tmp->next->redfile, R_OK))
		file_d = open(tmp->next->redfile, O_RDONLY);
	else
		return (-1);
	dup2(file_d, STDIN_FILENO);
	while (tmp->next && !ft_strncmp(tmp->next->cmd, "<", 2))
	{
		if (access(tmp->next->redfile, R_OK))
			return (-1);
		tmp = tmp->next;
	}
	if (tmp->next && !ft_strncmp(tmp->next->cmd, "|", 2))
		dup2(fd[1], STDOUT_FILENO);
	return (file_d);
}

int	redirect_firstnpt(t_arg *tmp, int fd[2])
{
	int		file_d;
	t_arg	*tmp2;

	tmp2 = NULL;
	if (tmp->cmd && !ft_strncmp(tmp->cmd, "<", 2))
	{
		if (tmp->next && access(tmp->next->cmd, R_OK))
			return (-1);
		file_d = open(tmp->next->cmd, O_RDONLY);
		dup2(file_d, STDIN_FILENO);
		if (tmp->next->next && tmp->next->next->cmd[0] == '>')
		{
			tmp2 = tmp->next->next;
			tmp = tmp->next;
		}
	}
	tmp = tmp->next->next;
	if (tmp)
	{
		close (file_d);
		file_d = open(tmp->redfile, O_RDONLY);
		dup2(file_d, STDIN_FILENO);
	}
	while (tmp && !ft_strncmp(tmp->cmd, "<", 2))
	{
		if (access(tmp->redfile, R_OK))
			return (-1);
		if (!tmp->next && tmp2)
		{
			if (!tmp2->cmd[1])
				file_d = open(tmp2->redfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
			else
				file_d = open(tmp2->redfile, O_CREAT | O_APPEND | O_RDWR, 0644);
		}
		tmp = tmp->next;
	}
	if (tmp && !ft_strncmp(tmp->cmd, "|", 2))
		dup2(fd[1], STDOUT_FILENO);
	return (file_d);
}
