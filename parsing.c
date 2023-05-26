/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:00 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/26 20:27:04 by aaghbal          ###   ########.fr       */
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
	int		i;
	int		c;
	int		j;
	char	*tmp;
	char	**tmp2;

	i = 0;
	c = 0;
	j = ++(*len);
	// if (line[j] == '?' || line[j] == 0)
	// {
	// 	str = ft_strjoin(str, t);
	// }
	while (ft_isalpha(line[j]) == 1 || ft_isdigit(line[j]) ==  1)
		j++;
	tmp = malloc(sizeof(char) * (j - (*len)) + 1);
	while ((*len) < j)
		tmp[i++] = line[(*len)++];
	tmp[i] = '\0';
	while (expo)
	{
		tmp2 = ft_split(expo->content, '=');
		if (ft_strncmp(tmp, tmp2[0], ft_strlen(tmp2[0])) == 0)
			str = ft_strjoin(str, tmp2[1]);
		free_tabb(tmp2);
		expo = expo->next;
	}
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
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\'' && line[(*len) - 1] == '\"' 
		&& get_next_quotes(line, 0, *len) == 0)
			str = single_quotes(line, str, len);
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\"')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
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
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\"' && line[(*len) - 1] == '\''
		&& get_next_quotes(line, 1, *len) == 0)
			str = double_quotes(line, str, len, NULL);
		if ((line[(*len)] == ' ' || line[(*len)] == '\t'
		|| check_token(line[(*len)])) && on == 0)
			break;
		if (line[(*len)] == '\'')
			on = 0;
		else
			str = append_char(str, line[(*len)]);
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
		if (line[(data->i)] != '\"' && line[data->i] != '\'')
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

