#include "minishell.h"

char	*export_pars(t_list *export_list, char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]))
	{
		printf("\e[0;31mminishell: export: not a valid identifier\n");
		g_ext_s = 1;
		return (NULL);
	}
	while (var[++i])
	{
		if (var[i] == '=')
		{
			if (!ft_isalnum(var[i - 1]))
			{
				printf ("export: %s: not a valid identifier\n", var);
				return (NULL);
			}
			else
				break ;
		}
		if (var[i] == '+')
		{
			if (var[i + 1] && var[i + 1] == '=' && ft_isalnum(var[i - 1]))
				return (add_var(export_list, var));
			else
			{
				printf ("export: %s: not a valid identifier\n", var);
				return (NULL);
			}
		}
	}
	return (var);
}
