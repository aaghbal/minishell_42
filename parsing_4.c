/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:14:04 by aaghbal           #+#    #+#             */
/*   Updated: 2023/07/06 15:18:02 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_quotes(char *line, int n, int i)
{
	char	c;

	c = '\"';
	if (n == 1)
		c = '\'';
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remove_sp(char *str)
{
	int		i;
	int		on;
	char	*tmp;

	on = 0;
	i = 0;
	tmp = NULL;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			on = 1;
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			if (on == 1)
				tmp = append_char(tmp, ' ');
			on = 0;
			tmp = append_char(tmp, str[i]);
		}
		i++;
	}
	free(str);
	return (tmp);
}

char	*ft_check_expand(t_list *expo, char *str, char *tmp)
{
	char	**tmp2;

	while (expo)
	{
		tmp2 = ft_split(expo->content, '=');
		if (tmp2 && !ft_strncmp(tmp, tmp2[0], ft_strlen(tmp)))
		{
			tmp2[1] = ft_remove_sp(tmp2[1]);
			str = ft_strjoin(str, tmp2[1]);
		}
		free_tabb(tmp2);
		expo = expo->next;
	}
	return (str);
}

char	*ft_expand(char *line, int *len, char *str, t_list *expo)
{
	int		i[2];
	char	*tmp;

	i[0] = 0;
	i[1] = ++(*len);
	if (line[i[1]] == '?')
	{
		str = ft_strjoin(str, ft_itoa(g_ext_s));
		i[1]++;
		return (str);
	}
	while (ft_isalnum(line[i[1]]) || line[i[1]] == '_')
		i[1]++;
	tmp = malloc(sizeof(char) * (i[1] - (*len)) + 1);
	if (!tmp)
		exit(0);
	while ((*len) < i[1])
		tmp[i[0]++] = line[(*len)++];
	tmp[i[0]] = '\0';
	str = ft_check_expand(expo, str, tmp);
	free(tmp);
	if (!str)
		str = ft_strdup("");
	return (str);
}

void	ft_increment(char *line, int *c, int *len, int *on)
{
	if (*c > 1)
	{
		*on = 1;
		*c = 0;
	}
	if (line[(*len)] == '$' && (ft_isalpha(line[(*len) + 1])))
	{
	}
	else
		(*len)++;
}
