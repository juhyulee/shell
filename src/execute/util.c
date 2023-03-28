/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/27 12:50:00 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//포인터가 있을 경우 프리하고, 널 리턴. 안전한 리턴 용도
void	*free_return_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = 0;
	return (0);
}

int	builtin_fd(t_cmd *cmd)
{
	int	fd;

	if (cmd->fd_in != -1)
	{
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	close(cmd->fd_pipe[0]);
	if (cmd->outpipe && (cmd->builtin <= CMD_BT_ENV))
	{
		fd = open("/tmp/.temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			throw_error("msh: ", "open file error", "", 1);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}

//builtin인지 체크 후 실행 함수
int	exec_builtin(t_cmd *cmd, t_env *env)
{
	builtin_fd(cmd);
	if (cmd->builtin == CMD_BT_CD)
		return (builtin_cd(cmd->argv, env));
	else if (cmd->builtin == CMD_BT_ECHO)
		return (builtin_echo(cmd->argv));
	else if (cmd->builtin == CMD_BT_ENV)
		return (builtin_env(cmd->argv, env));
	else if (cmd->builtin == CMD_BT_PWD)
		return (builtin_pwd(cmd->argv, env));
	else if (cmd->builtin == CMD_BT_EXIT)
		return (builtin_exit(cmd->argv));
	else if (cmd->builtin == CMD_BT_EXPORT)
		return (builtin_export(cmd->argv, env));
	else if (cmd->builtin == CMD_BT_UNSET)
		return (builtin_unset(cmd->argv, env));
	else
		return (1);
}

void	builtin_pipe_reopen(t_cmd *cmd)
{
	int	fd;

	cmd->cnt--;
	if (!cmd->outpipe)
		return ;
	fd = open("/tmp/.temp", O_RDONLY);
	cmd->fd_pipe[0] = fd;
}
