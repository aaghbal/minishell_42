/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:35 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 09:47:59 by zel-kach         ###   ########.fr       */
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
			if (!input[0] && !delimiter[i])
				break ;
			if (!ft_strncmp(delimiter[i], input, ft_strlen(input))
				&& (ft_strlen(input) == ft_strlen(delimiter[i])))
				break ;
			if (!tmp->next || (tmp->next && tmp->next->cmd[0] == '|'))
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

int	here_doc2(t_arg *tmp, int fd[2], t_arg *file, t_arg *file_out)
{
	int		i;

	i = 0;
	here_doc3(tmp, file, fd);
	if (file_out)
		i = redirect(file_out);
	return (i);
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
			file_out = tmp;
			file = file->next;
			tmp = tmp->next;
		}
		file = file->next;
		tmp = tmp->next;
	}
	return (here_doc2(tmp, fd, file, file_out));
}
