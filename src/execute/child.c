/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:06:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/27 13:30:11 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//child 내에서 error로 exit할 경우
int	child_exit(char *mes1, char *mes2, char *mes3, int code)
{
	ft_putstr_fd("\033[31m\033[9m", 2);
	ft_putstr_fd(mes1, 2);
	ft_putstr_fd(mes2, 2);
	ft_putendl_fd(mes3, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(code);
}

//child 내에서 pipe 있을 경우 열고 dup
void	chk_pipe_child(t_cmd *cmd)
{
	if (cmd->outpipe)
	{
		dup2(cmd->fd_pipe[1], 1);
	}
	close(cmd->fd_pipe[0]);
	close(cmd->fd_pipe[1]);
}

void	get_file_fd_child(t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		child_exit("msh: no such file or directory: ", \
				cmd->filename, "", 0);
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out && !cmd->outpipe)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
		cmd->fd_in = -1;
	}
}

int	child_proc(t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	get_file_fd_child(cmd);
	chk_pipe_child(cmd);
	if (execve(cmd->filename, cmd->argv, environ) == -1)
	{
		if (cmd->filename)
			child_exit("msh: ", cmd->filename, ": command not found", 127);
		else
			child_exit("msh: command not found", "", "", 127);
	}
	exit(0);
}
