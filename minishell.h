/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:52:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 09:43:16 by zel-kach         ###   ########.fr       */
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
# include <paths.h>

// # define NOR 0
// # define APND 4
// # define TRNC 5

int	g_ext_s;

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
	char			key;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int		i;
	char	*str;
}	t_data;

/*---commands---*/
void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list);
void	my_export(t_list *export_list, t_list *env_list, char *var);
void	my_pwd(t_list *export_list);
void	my_exit(t_arg *cmd);
void	my_cd(t_arg *cmd, t_list *expo, t_list *env);
void	my_unset(char *cmd, t_list *export_list, t_list *env_list);
void	my_exec_cmd(t_arg *cmd, int pi);
void	execute(t_arg *tmp, t_list *export_list, t_list *env_list);
void	my_exec_cmd_a1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_b1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_c1(t_arg *cmd, int pi, int current_pipe);
void	my_exec_cmd_c2(t_arg *cmd, int pi);
void	my_exec_cmd_d1(t_arg *cmd, int pi);
void	my_exec_cmd_e1(t_arg *cmd, int pi);
void	my_echo(t_arg *cmd);
void	my_env(t_list *env_list);
int		redirect(t_arg *tmp);
int		here_doc(t_arg *tmp, int fd[2]);
void	doc_handler(int signal);
void	unset_export(char *cmd, t_list *export_list);
void	close_file(int file_d, int fd[2]);
int		reset(int pid);
int		parent(int file_d, int s, int fd[2]);
int		hered_check(t_arg *tmp);
int		redirect_inpt(t_arg *tmp, int fd[2]);
int		get_next_inptred(t_arg *arg);
char	*export_pars(t_list *export_list, char *var);
char	*add_var(t_list *export_list, char *var);
void	multi_red(t_arg *tmp);
int		execute_child(t_arg *tmp, int fd[2], int fd2[2], int s);
int		execute_parent(t_arg *tmp, int fd[2], int fd2[2], int s);
t_arg	*if_unset(t_arg *tmp, t_list *export_list, t_list *env_list);
t_arg	*if_export(t_arg *tmp, t_list *export_list, t_list *env_list);
void	ft_pwd(t_list *expo);
void	ft_oldpwd(t_list *expo);
int		hered_check(t_arg *tmp);
char	**alloc(t_arg	*file);
char	**list_to_tabs(t_list *list);
char *get_key_exp(t_list *exp, char *key);

/*---signals---*/
void	sighandler(int signal);
void	sighandler_child(int signal);
void	sighandler_child2(int signal);

/*---parsing---*/
t_token	*ft_tokenlast(t_token *lst);
t_token * new_token(char *cmd, t_type type, int k);
t_arg	*newarg_token(char *cmd, t_type type);
t_arg	*ft_arglast(t_arg *lst);
t_type	get_type(char *str);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	add_free(t_data *data, t_token **token, char *line);
void	ft_argadd_back(t_arg **lst, t_arg *new);
void	is_token(t_data *data, char *line);
void	default_cmd(t_data *data, char *line, t_list *expo);
void	free_tabb(char **tabb);
void	is_arg(t_token *tmp, t_arg **arg);
void	free_list(t_token *tabb);
void	append_word(t_token **tmp, t_arg **arg);
void	apend_redirection(t_token **tmp, t_arg **arg);
char	**alloc_arg(char **args, char *cmd);
char	*append_char(char *str, char c);
char	*print_token(int n);
char	*double_quotes(char *line, char *str, int *len, t_list *expo);
char	*single_quotes(char *line, char *str, int *len);
char	*char_to_str(char *line);
char	*get_token(char *line);
int		get_end(char *line, int i);
int		token_line(char *line, t_list *export_list, t_list *env_list);
int		check_token(char c);
int		is_char(char c);
int		ft_parsing_2(t_token **token);
int		ft_parsing(char *tmp);
char	*ft_expand(char *line, int *len, char *str, t_list *expo);
void	print_epxport(t_list *export_list);
int		get_next_pip(t_arg *arg);
int		get_next_red(t_arg *arg);
int		is_char(char c);
int		is_char(char c);
int		get_token_pars(char *line);
int		check_line_2(char *str);
int		check_line(char *str);
int		parsing(char *str);
void	free_arg(t_arg *str);
int		r_inpt(t_arg *tmp, int fd[2], int fd2[2]);
int		current_pipe(t_arg *tmp, int fd[2], int fd2[2], int s);
int		execute_hered(t_arg *tmp, int fd[2], int fd2[2]);
t_arg	*first_redirect(t_arg *tmp);

#endif