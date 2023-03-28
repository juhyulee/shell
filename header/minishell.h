/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:21:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/28 17:42:32 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHE 0
# define DFL 1
# define IGN 2
# define STDOUT_BU 11
# define STDIN_BU 10

# include "ansi_color.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

extern char	**environ;

enum e_type
{
	EMPTY = 0,
	RED_INFILE = 1 << 0,
	RED_HEREDOC = 1 << 1,
	RED_OUTFILE = 1 << 2,
	RED_APPEND = 1 << 3,
	RED = 1 << 4,
	PIP = 1 << 5,
	CMD = 1 << 6,
	CMD_SQ,
	CMD_DQ,
	CMD_BT_PWD,
	CMD_BT_ECHO,
	CMD_BT_ENV,
	CMD_BT_CD,
	CMD_BT_EXIT,
	CMD_BT_EXPORT,
	CMD_BT_UNSET
};

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}			t_env;

typedef struct s_node
{
	char			*str;
	int				type;
	struct s_node	*next;
}			t_node;

typedef struct s_error
{
	int	quote;
	int	pipe;
	int	str;
}			t_error;

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	int		fd_pipe[2];
	char	outpipe;
	char	inpipe;
	int		fd_in;
	int		fd_out;
	int		cnt;
	int		status;
	int		builtin;
	char	**path;
	t_list	*red_file;
}			t_cmd;

# define PIP_IN 2
# define PIP_OUT 4

void		sig_handler(int signo);
void		signal_exit(int signum);
void		sig_init(void);
char		*get_key(char *str);
char		*get_val(char *str);
void		env_back(char *str, t_env **env);
void		make_env(char **envp, t_env **env);
char		*middle_inside(char *str, char *start, char *value, int val_len);
char		*change_env_sub(int status, char *start, t_node *head);
char		*change_env_dq(char *start, t_node *head, t_env *env);
int			change_env(t_node *head, t_env *env, int status);
void		check_lst_env(t_node *head, t_env *env, int status);
int			check_parse_error_red(char *line);
char		**ft_split_replace(char const *s, char c, char replace_char);
void		init_head(t_node **head);
void		main_init(int ac, char **envp, t_env **env, t_node **head);
t_node		*init_node_node(t_node *head);
int			new_node_empty(t_node *prev, char *line);
int			new_node_quote(t_node *prev, char *line);
int			new_node_pipe(t_node *prev);
int			new_node_node(t_node *prev, char *line);
int			new_node_eof(t_node *prev, char *line);
int			error_parsing(char *line);
int			built_cmp(char *line);
int			parse(char *line, t_node **head);
int			get_red_type(char *line);
int			new_node_red(t_node *prev, char *line);
int			ft_strcmp(const char *s1, const char *s2);
int			is_whitespace(char *line);
int			is_quote(char c);
int			is_space(char c);
int			is_pipe(char c);
int			is_red(char c);
int			throw_error(char *mes1, char *mes2, char *mes3, int code);
char		*ft_charjoin(char *s1, char s2);
void		check_quote_lst(t_node *head);
void		init_error_struct(t_error *error);
int			check_quote(char line, int quote);
char		*ft_strndup(char *s, int i);
void		free_node(t_node *head);
int			ft_env_strnstr(const char *haystack, const char *needle, int len);
void		merge_cmd(t_node *head);

//exec folder -----

//exec
int			execute(t_node *head, t_env *env, int status);
int			wait_all(t_cmd *cmd);
void		finish_cmd(t_cmd *cmd);
t_node		*execute_init(t_node *head);
void		print_cmd(t_cmd *cmd);

//init cmd
char		*get_env_var(char *const *envp, char *var);
t_cmd		*init_cmd(t_env *env, int status);
void		free_cmd(t_cmd *cmd);
void		mini_lstclear(t_list *lst);

//parent
t_node		*parse_cmd_parent(t_node *node, \
			t_cmd *cmd, char **path, t_env *env);
t_node		*toword_end_node(t_node *node);
t_node		*reset_parent(t_cmd *cmd, t_node *node);
void		open_pipe(t_cmd *cmd);

//child_proc
int			child_proc(t_cmd *cmd);
int			child_exit(char *mes1, char *mes2, char *mes3, int code);
void		chk_pipe_child(t_cmd *cmd);
//file_open
int			fd_dup_close(int fd, int stdfd);
void		get_file_fd_child(t_cmd *cmd);
t_node		*open_file(t_node *node, t_cmd *cmd, t_env *env);
char		*heredoc_check_env(char *argv, t_env *env, int status);

//util
void		*free_return_null(void *ptr);
int			exec_builtin(t_cmd *cmd, t_env *env);
void		builtin_pipe_reopen(t_cmd *cmd);

//command
char		*get_full_cmd(t_cmd *cmd, char **path, t_node *node);
int			get_cmd(t_node *node, t_cmd *cmd, char **path);
char		**new_argv(char *str);
char		**join_argv(char **argv, char *str);

//builtin
int			builtin_cd(char **argv, t_env *env);
int			builtin_echo(char **argv);
int			builtin_env(char **argv, t_env *env);
int			builtin_exit(char **argv);
int			builtin_export(char **argv, t_env *env);
int			builtin_pwd(char **argv, t_env *env);
int			builtin_unset(char **argv, t_env *env);
char		*get_env_value(t_env *env, char *str);
char		*get_up_dir(char *pwd);
char		*get_env_value(t_env *env, char *str);

#endif
