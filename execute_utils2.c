
#include "minishell.h"

int	current_pipe(t_arg *tmp, int fd[2], int fd2[2], int s)
{
	int	file_d;

	file_d = 0;
	if (tmp->next->cmd[0] == '>')
		file_d = open(tmp->next->next->cmd, O_CREAT | O_TRUNC, 0777);
	close_file(file_d, fd2);
	close_file(file_d, fd);
	if (s)
		close(s);
	return (0);
}

int	r_inpt(t_arg *tmp, int fd[2], int fd2[2])
{
	int	file_d;

	file_d = redirect_inpt(tmp, fd);
	if (file_d == -1)
	{
		printf ("minishell: %s: No such file or directory\n",
			tmp->next->redfile);
		close_file(file_d, fd2);
		close_file(file_d, fd);
		exit(1);
	}
	return (file_d);
}

t_arg	*first_redirect(t_arg *tmp)
{
	int	file_d;

	if (tmp->next &&  tmp->cmd[0] == '>' && !tmp->redfile)
	{
		file_d = open(tmp->next->cmd, O_CREAT | O_RDWR, 0644);
		tmp = tmp->next;
	}
	else
		file_d = open(tmp->redfile, O_CREAT | O_RDWR, 0644);
	tmp = tmp->next;
	close (file_d);
	return (tmp);
}

t_arg	*if_export(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = 0;
	if (tmp && tmp->next && tmp->next->cmd[0] == '|')
		tmp = tmp->next;
	else if (tmp)
	{
		while (tmp && tmp->arg[++i])
			my_export(export_list, env_list, tmp->arg[i]);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}

t_arg	*if_unset(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = 0;
	if (tmp->next && tmp->next->cmd[0] == '|')
		tmp = tmp->next;
	else
	{
		while (tmp->arg[++i])
			my_unset(tmp->arg[i], env_list, export_list);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}
