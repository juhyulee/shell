/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/27 13:36:49 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	fd_dup_close(int fd, int stdfd)
{
	dup2(fd, stdfd);
	close(fd);
	return (0);
}

int	get_heredoc(char *str, t_env *env, int status)
{
	char	*line;
	char	*limiter;
	int		fd;
	char	*filename;

	limiter = ft_strjoin(str, "\n");
	write(1, "heredoc>", 9);
	line = heredoc_check_env(get_next_line(0), env, 0);
	filename = ft_strjoin("/tmp/", str);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (line && ft_strncmp(line, limiter, ft_strlen(line)) != 0)
	{
		write(1, "heredoc>", 9);
		write(fd, line, ft_strlen(line));
		free(line);
		line = heredoc_check_env(get_next_line(0), env, status);
	}
	if (line)
		free(line);
	close(fd);
	fd = open(filename, O_RDONLY);
	free(limiter);
	free(filename);
	return (fd);
}

void	file_close(int type, t_cmd *cmd)
{
	if (type & RED_INFILE || type & RED_HEREDOC)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (type & RED_OUTFILE || type & RED_APPEND)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

t_node	*open_file(t_node *node, t_cmd *cmd, t_env *env)
{
	t_node	*red;

	red = node->next;
	while (red && red->type != RED && red->type != PIP)
		red = red->next;
	if (!red->str)
	{
		throw_error("msh: syntax error near unexpected token \'", \
					node->next->str, "\'", 1);
		return (0);
	}
	file_close(node->type, cmd);
	if (node->type & RED_INFILE)
		cmd->fd_in = open(red->str, O_RDONLY);
	else if (node->type & RED_HEREDOC)
		cmd->fd_in = get_heredoc(red->str, env, cmd->status);
	else if (node->type & RED_OUTFILE)
		cmd->fd_out = open(red->str, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (node->type & RED_APPEND)
		cmd->fd_out = open(red->str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		cmd->filename = ft_strdup(red->str);
	return (red);
}
