/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:06:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/27 12:55:52 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	execute(t_node *head, t_env *env, int status)
{
	t_node	*node;
	t_cmd	*cmd;
	pid_t	pid;

	cmd = init_cmd(env, status);
	node = execute_init(head);
	while (node)
	{
		parse_cmd_parent(node, cmd, cmd->path, env);
		if (cmd->builtin >= CMD_BT_PWD)
		{
			cmd->status = exec_builtin(cmd, env);
			builtin_pipe_reopen(cmd);
		}
		else
		{
			pid = fork();
			if (!pid)
				exit(child_proc(cmd));
		}
		node = reset_parent(cmd, node);
	}
	status = wait_all(cmd);
	finish_cmd(cmd);
	return (status);
}

void	finish_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->path && cmd->path[++i])
		free(cmd->path[i]);
	free(cmd->path);
	free(cmd);
	dup2(STDOUT_BU, 1);
	dup2(STDIN_BU, 0);
}

//printf("ifstop %0 d stopsig % 3d\nifexit % 3d, exitstt % 3d\nifsign %
//3d termsig % 3d\n", WIFSTOPPED(status),WSTOPSIG(status),  WIFEXITED(status),
//WEXITSTATUS(status),WIFSIGNALED(status), WTERMSIG(status) );
//exitcode....
int	wait_all(t_cmd *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (cmd->cnt > i)
	{
		if (wait(&status) == -1 && WSTOPSIG(status) != 0)
		{
			ft_putnbr_fd(WSTOPSIG(status), 2);
			throw_error("", ": msh: ", "unexit child", -1);
		}
		i++;
	}
	if (!cmd->cnt)
		return (cmd->status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (WSTOPSIG(status));
}

t_node	*execute_init(t_node *head)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (head->next);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	printf("filename is %s\n", cmd->filename);
	while (cmd->argv[++i])
		printf("node is %s\n", cmd->argv[i]);
	printf("cmd cnt %d*\n", cmd->cnt);
}
