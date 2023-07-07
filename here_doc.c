/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:35 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/07 09:04:20 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc4(t_arg *tmp, int fd[2], int i, char **delimiter)
{
	char	*input;

	input = NULL;
	while (i > -1)
	{
		input = readline(">");
		while (1)
		{
			if (!input)
				exit(0);
			if (!input[0] && !delimiter[i])
				break ;
			if (!ft_strncmp(delimiter[i], input, ft_strlen(input))
				&& (ft_strlen(input) == ft_strlen(delimiter[i])))
				break ;
			if (!tmp->next || (tmp->next && tmp->next->cmd[0] == '|')
				|| (tmp->next && ft_strncmp(tmp->next->cmd, "<<", 3)))
				ft_putendl_fd(input, fd[1]);
			input = readline(">");
		}
		i--;
		tmp = tmp->next;
	}
}

void	here_doc3(t_arg *tmp, t_arg *file, int fd[2])
{
	char	**delimiter;
	int		i;

	i = 0;
	delimiter = alloc(file);
	while (file && !ft_strncmp(file->cmd, "<<", 3))
	{
		delimiter[i] = ft_strdup(file->redfile);
		i++;
		file = file->next;
	}
	here_doc4(tmp, fd, i - 1, delimiter);
}

void	here_doc2(t_arg *tmp, int fd[2], t_arg *file)
{
	int		i;

	i = 0;
	here_doc3(tmp, file, fd);
}

int	here_doc(t_arg *tmp, int fd[2])
{
	t_arg	*file;
	t_arg	*file_out;

	file = tmp;
	file_out = NULL;
	if (ft_strncmp(file->cmd, "<<", 3))
	{
		if (tmp->next && tmp->next->cmd[0] == '>')
		{
			file = file->next;
			tmp = tmp->next;
		}
		file = file->next;
		tmp = tmp->next;
	}
	return (here_doc2(tmp, fd, file), 0);
}
