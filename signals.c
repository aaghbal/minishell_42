/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:52:16 by zel-kach          #+#    #+#             */
/*   Updated: 2023/07/04 15:48:48 by aaghbal          ###   ########.fr       */
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
}

void	sighandler_child(int signal)
{
	if (signal == 2 || signal == 3)
		return ;
}

t_token	*new_token(char *cmd, t_type type, int k)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		exit(0);
	node->cmd = ft_strdup(cmd);
	node->key = k;
	if (type == NONE)
		return (NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

t_arg	*newarg_token(char *cmd, t_type type)
{
	t_arg	*node;

	node = (t_arg *)malloc(sizeof(t_arg));
	if (!node)
		exit(0);
	node->cmd = ft_strdup(cmd);
	node->arg = alloc_arg(NULL, cmd);
	node->type = type;
	node->redfile = NULL;
	node->next = NULL;
	return (node);
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(3, sighandler);
	signal(2, sighandler);
}
