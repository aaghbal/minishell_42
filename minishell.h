/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:52:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:52:10 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"
# include <string.h>
# include <sys/errno.h>


# define NOR 0
# define PIPE 1
# define FPIPE 2
# define EPIPE 3
# define APND 4
# define TRNC 5

int	g_fd[3][2];

typedef enum type{
	tokenword,
	tokenpipe,
	redirections,
	NONE
}	t_type;

typedef struct s_arg{
	char			*cmd;
	char			*redfile;
	char			**arg;
	t_type			type;
	struct s_arg	*next;
	int				t_pipes;
}	t_arg;

typedef struct s_token{
	char			*cmd;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int		i;
	char	*str;
}	t_data;

/*---commands---*/
void	all_cmd(t_arg *cmd, t_list *export_list,
			t_list *env_list, int pi);
void	my_export(t_list *export_list, t_list *env_list,
			char *var, int pi);
void	my_pwd(t_arg *cmd, int pi);
void	my_exit(void);
void	my_cd(t_arg *cmd);
void	my_env(t_list *env, int pi);//redirect
void	my_unset(t_list *env);
void	my_exec_cmd(t_arg *cmd, int pi);
void	my_exec_cmd_a1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_b1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_c1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_c2(t_arg *cmd, int pi);
void	my_exec_cmd_d1(t_arg *cmd, int pi);
void	my_exec_cmd_e1(t_arg *cmd, int pi);
void	my_echo(t_arg *cmd, int pi);
void	my_echo1(t_arg *cmd, int pi);
void	my_echo2(t_arg *cmd, int pi);
void	my_echo3(t_arg *cmd, int pi);
void	my_echo4(t_arg *cmd);

/*---signals---*/
void	sighandler(int signal);

/*---parsing---*/
t_token	*ft_tokenlast(t_token *lst);
t_token	*new_token(char *cmd, t_type type);
t_arg	*newarg_token(char *cmd, t_type type);
t_arg	*ft_arglast(t_arg *lst);
t_type	get_type(char *str);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	add_free(t_data *data, t_token **token);
void	ft_argadd_back(t_arg **lst, t_arg *new);
void	is_token(t_data *data, char *line);
void	default_cmd(t_data *data, char *line);
void	free_tabb(char **tabb);
void	is_arg(t_token *tmp, t_arg **arg);
void	free_list(t_token *tabb);
void	append_word(t_token **tmp, t_arg **arg);
void	apend_redirection(t_token **tmp, t_arg **arg);
char	**alloc_arg(char **args, char *cmd);
char	*append_char(char *str, char c);
char	*print_token(int n);
char	*double_quotes(char *line, char *str, int *len);
char	*single_quotes(char *line, char *str, int *len);
char	*char_to_str(char *line);
char	*get_token(char *line);
int		get_end(char *line, int i);
int		token_line(char *line, t_list *export_list, t_list *env_list);
int		check_token(char c);
int		is_char(char c);
int		ft_parsing_2(t_token **token);
int		ft_parsing(char *tmp);

#endif
