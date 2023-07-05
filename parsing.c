/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:00 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/05 19:47:03 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_d_quote(char *line, char *str, int *len, t_list *expo)
{
	int	on;
	int	c;

	c = 0;
	on = 1;
	while (line[(*len)])
	{
		if (line[(*len)] == '$' && (ft_isalpha(line[(*len) + 1])
				|| line[(*len) + 1] == '?'))
			str = ft_expand(line, len, str, expo);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t'
				|| token_found(line[*len])) && on == 0)
			break ;
		else if (line[(*len)] == '\'' && on == 0)
			str = single_quotes(line, str, len);
		else if (line[(*len)] == '\"')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
		if (line[(*len)] == '\0')
			break ;
		ft_increment(line, &c, len, &on);
	}
	return (str);
}

char	*double_quotes(char *line, char *str, int *len, t_list *expo)
{
	++(*len);
	str = check_d_quote(line, str, len, expo);
	return (str);
}

void	ft_increment_s(int *c, int *len, int *on)
{
	if (*c > 1)
	{
		*on = 1;
		*c = 0;
	}
	(*len)++;
}

char	*check_s_quote(char *line, char *str, int *len)
{
	int	on;
	int	c;

	c = 0;
	on = 1;
	while (line[(*len)])
	{
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
				|| token_found(line[*len])) && on == 0)
			break ;
		else if (line[(*len)] == '\"' && on == 0)
			str = double_quotes(line, str, len, NULL);
		else if (line[(*len)] == '\'')
		{
			on = 0;
			c++;
		}
		else
			str = append_char(str, line[(*len)]);
		if (line[(*len)] == '\0')
			break ;
		ft_increment_s(&c, len, &on);
	}
	return (str);
}

char	*single_quotes(char *line, char *str, int *len)
{
	++(*len);
	if (line[(*len)] != '\'')
		str = append_char(str, line[(*len)++]);
	str = check_s_quote(line, str, len);
	return (str);
}
