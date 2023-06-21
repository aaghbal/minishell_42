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
	char c;
	
	c = '\"';
	if (n == 1)
		c = '\'';
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return(0);
}
char	*ft_expand(char *line, int *len, char *str,  t_list *expo)
{
	int		i[2];
	char	*tmp;
	char	**tmp2;

	i[0] = 0;
	i[1] = ++(*len);
	while (ft_isalpha(line[i[1]]) == 1 || ft_isdigit(line[i[1]]) ==  1)
		i[1]++;
	tmp = malloc(sizeof(char) * (i[1] - (*len)) + 1);
	while ((*len) < i[1])
		tmp[i[0]++] = line[(*len)++];
	tmp[i[0]] = '\0';
	while (expo)
	{
		tmp2 = ft_split(expo->content, '=');
		if (!ft_strncmp(tmp, tmp2[0], ft_strlen(tmp2[0])) 
		&& ft_strlen(tmp2[0]) == ft_strlen(tmp))
			str = ft_strjoin(str, tmp2[1]);
		free_tabb(tmp2);
		expo = expo->next;
	}
	free(tmp);
	if (!str)
		str = ft_strdup("");
	return(str);
}

char	*double_quotes(char *line,char *str, int *len, t_list *expo)
{
	int on;

	on = 1;
	++(*len);
	if (line[(*len)] != '\"' && line[(*len)] != '$')
		str = append_char(str, line[(*len)++]);
	while (line[(*len)])
	{
		if (line[(*len)] == '$' && ft_isalpha(line[(*len) + 1]))
			str = ft_expand(line, len,str, expo);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break;
		else if (line[(*len)] == '\'' && on == 0)
			str = single_quotes(line, str, len);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break;
		else if (line[(*len)] == '\"')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
		 if (line[(*len)] == '\0')
			break;
			(*len)++;
	}
	return (str);
}

char	*single_quotes(char *line,char *str, int *len)
{
	int on;

	on = 1;
	++(*len);
	if (line[(*len)] != '\'')
		str = append_char(str, line[(*len)++]);
	while (line[(*len)])
	{
		if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break;
		else if (line[(*len)] == '\"' && on == 0)
			str = double_quotes(line, str, len, NULL);
		else if ((line[(*len)] == ' ' || line[(*len)] == '\t') && on == 0)
			break;
		else if (line[(*len)] == '\'')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
		if (line[(*len)] == '\0')
			break;
		(*len)++;
	}
	return (str);
}

void	default_cmd(t_data *data, char *line, t_list *expo)
{
	while (line[(data->i)] && !is_char(line[data->i]))
	{
		if (line[data->i] == '$' && ft_isalpha(line[data->i + 1]))
			data->str = ft_expand(line, &data->i,data->str, expo);
		else if (line[(data->i)] != '\"' && line[data->i] != '\'' && line[(data->i)])
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
