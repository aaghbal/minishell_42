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

// void	sighandler(int signal)
// {
// 	char *pp[] = {"stty", "-echoctl", NULL};
// 		if(!fork())
// 		{
// 			if (execve ("/bin/stty", pp, NULL) == -1)
// 				printf ("error\n");
// 		}
// 		wait (0);

// if (signal == 3)
// {	
// 	return ;
// }
// else if (signal == 11)
// {
// 	printf("out\n");
// 	exit (0);
// }
// else if (signal == 2)
// {
// 	// write(1, "\n", 1);
// 	// write(1, "minishell ➜ ", 12);
// 	return ;
// }
// }
