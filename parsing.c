/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:00 by aaghbal           #+#    #+#             */
/*   Updated: 2023/06/13 13:42:54 by aaghbal          ###   ########.fr       */
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
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
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
		if (tmp2 && !ft_strncmp(tmp, tmp2[0], ft_strlen(tmp2[0])))
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
	while (ft_isalpha(line[i[1]]) == 1 || ft_isdigit(line[i[1]]) == 1
		|| line[i[1]] == '_')
		i[1]++;
	tmp = malloc(sizeof(char) * (i[1] - (*len)) + 1);
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

char	*check_d_quote(char *line, char *str, int *len, t_list *expo)
{
	int	on;
	int	c;

	c = 0;
	on = 1;
	while (line[(*len)])
	{
		if (line[(*len)] == '$' && (ft_isalpha(line[(*len) + 1])))
			str = ft_expand(line, len, str, expo);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break ;
		else if (line[(*len)] == '\'' && on == 0)
			str = single_quotes(line, str, len);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break ;
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
	if (line[(*len)] != '\"' && line[(*len)] != '$')
		str = append_char(str, line[(*len)++]);
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
		if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break ;
		else if (line[(*len)] == '\"' && on == 0)
			str = double_quotes(line, str, len, NULL);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break ;
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

void	default_cmd(t_data *data, char *line, t_list *expo)
{
	while (line[(data->i)] && !is_char(line[data->i]))
	{
		if (line[data->i] == '$' && (ft_isalpha(line[data->i + 1])
				|| line[data->i + 1] == '_'))
			data->str = ft_expand(line, &data->i, data->str, expo);
		else if (line[(data->i)] != '\"' && line[data->i] != '\''
				&& line[(data->i)])
			data->str = append_char(data->str, line[(data->i)++]);
		else
		{
			if (line[(data->i)] == '\"')
				data->str = double_quotes(line, data->str, &(data->i), expo);
			else if (line[data->i] == '\'')
				data->str = single_quotes(line, data->str, &(data->i));
		}
	}
}
