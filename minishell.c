/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:49:22 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/06 10:49:24 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char ** av, char *envp[])
{
	(void)ac;
	(void)av;
	(void)envp;
	char *input;
	int c = 0;
	int k = 0;


	while (1)
	{

		input = readline("minishell> ");
		if (!input)
			break;
		if (c % 2 != 0 || k % 2 != 0)
			break;
		add_history(input);
		token_line(input);
		free(input);
	}
	return (0);
}
