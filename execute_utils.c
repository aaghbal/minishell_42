/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:51:53 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:51:54 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset(int pid)
{
	waitpid(pid, &g_ext_s, 0);
	g_ext_s = WEXITSTATUS(g_ext_s);
	return (0);
}

int	parent(int file_d, int s, int fd[2])
{
	if (s)
		close(s);
	s = dup(fd[0]);
	close_file(file_d, fd);
	return (s);
}
