/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:52:16 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:52:17 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sighandler(int signal)
{
	if (signal == 3)
		return ;
	else if (signal == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_ext_s = 1;
		return ;
	}
	else if (signal == 11)
	{
		write(1, "exit\n", 5);
		exit (0);
	}
}

void	sighandler_child(int signal)
{
	if (signal == 3)
	{
		write(1, "Quit: 3\n", 9);
		g_ext_s = 131;
	}
	else if (signal == 2)
	{
		write(1, "\n", 1);
		g_ext_s = 130;
	}
	else if (signal == 11)
		exit (0);
}
