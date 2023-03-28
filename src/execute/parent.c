/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/27 12:46:54 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_node	*parse_cmd_parent(t_node *node, t_cmd *cmd, char **path, t_env *env)
{
	while (node)
	{
		while (node->next && node->type == EMPTY)
			node = node->next;
		if (node->type && node->type >= CMD)
			get_cmd(node, cmd, path);
		else if (node->type && node->type < RED)
			node = open_file(node, cmd, env);
		else if (node->type == PIP)
		{
			open_pipe(cmd);
			break ;
		}
		if (node)
			node = node->next;
	}
	return (node);
}

t_node	*toword_end_node(t_node *node)
{
	while (node && node->type != PIP)
		node = node->next;
	if (node && node->type == PIP)
		node = node->next;
	return (node);
}

void	unlink_red_files(t_node *node)
{
	char	*temp;

	while (node->next && node->type != PIP)
	{
		if (node->type == RED)
		{
			temp = ft_strjoin("/tmp/", node->str);
			unlink(temp);
			free(temp);
		}
		node = node->next;
	}
}

t_node	*reset_parent(t_cmd *cmd, t_node *node)
{
	dup2(STDOUT_BU, 1);
	dup2(STDIN_BU, 0);
	unlink_red_files(node);
	close(cmd->fd_pipe[1]);
	if (cmd->outpipe)
	{
		dup2(cmd->fd_pipe[0], 0);
		cmd->inpipe = 1;
	}
	close(cmd->fd_out);
	close(cmd->fd_in);
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	close(cmd->fd_pipe[0]);
	cmd->outpipe = 0;
	cmd->builtin = 0;
	cmd->cnt++;
	cmd->filename = free_return_null(cmd->filename);
	cmd->argv = free_return_null(cmd->argv);
	cmd->argv = 0;
	return (toword_end_node(node));
}

void	open_pipe(t_cmd *cmd)
{
	pipe(cmd->fd_pipe);
	cmd->outpipe = 1;
}
