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

int	hered_check(t_arg *tmp)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "<<", 3))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**alloc(t_arg	*file)
{
	int		i;
	char	**delem;

	i = 0;
	if (!ft_strncmp(file->cmd, "<<", 3))
		i++;
	while (file && file->next && !ft_strncmp(file->next->cmd, "<<", 3))
	{
		i++;
		file = file->next;
	}
	delem = malloc(sizeof(char *) * i + 1);
	return (delem);
}

int	here_doc2(t_arg *tmp, int fd[2])
{
	char	**delimiter;
	int		file_d;
	char	*input;
	t_arg	*file;
	int		i;

	delimiter = NULL;
	file_d = 0;
	i = 0;
	file = tmp;
	delimiter = alloc(file);
	if (!ft_strncmp(file->cmd, "<<", 3))
	{
		delimiter[i] = ft_strdup(file->redfile);
		file = file->next;
		i++;
	}
	else
	{
		file = file->next;
		tmp = tmp->next;
	}
	while (file && !ft_strncmp(file->cmd, "<<", 3))
	{
		delimiter[i] = ft_strdup(file->redfile);
		i++;
		file = file->next;
	}
	i--;
	file = NULL;
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
	if (file)
		file_d = redirect(file);
	return (file_d);
}


int	here_doc(t_arg *tmp, int fd[2])
{
	return (here_doc2(tmp, fd));
}
