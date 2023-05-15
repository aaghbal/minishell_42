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
	int i;
	int j;

	i = 0;
	j = 0;
	while (1)
	{

		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		char *tmp = malloc(sizeof(char) * ft_strlen(input) + 1);
		ft_strlcpy(tmp, input, ft_strlen(input) + 1);
		if (ft_parsing(tmp) == 0 || token_line(input) ==  0)
		{
			write(1, "syntax error\n", 13);
			continue;
		}
		continue;
		free(input);
	}
	return (0);
}
