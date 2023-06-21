/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:59:21 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/20 20:27:05 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_pip(t_arg *arg)
{
	int c;

	c = 0;
	while (arg)
	{
		if (arg->cmd[0] == '|')
			c++;
		arg = arg->next;
	}
	return(c);
}

int	get_next_red(t_arg *arg)
{
	int c;

	c = 0;
	while (arg)
	{
		if (arg->cmd[0] == '>')
			c++;
		arg = arg->next;
	}
	return(c);
}

int	get_next_inptred(t_arg *arg)
{
	int c;

	c = 0;
	while (arg)
	{
		if (arg->cmd[0] == '<')
			c++;
		arg = arg->next;
	}
	return(c);
}

int is_char(char c)
{
	if (c == ' ' || c == '\t' || check_token(c))
		return (1);
	return(0);
}

int	check_line_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\"'
			&& str[i] != '\'' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}