/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 18:57:07 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//path 붙인 명령어 반환
char	*get_full_cmd(t_cmd *cmd, char **path, t_node *node)
{
	int		i;
	char	*full_cmd;

	i = 0;
	if (node->type >= CMD_BT_PWD || !path)
		return (ft_strdup(cmd->filename));
	if (access(cmd->filename, F_OK | X_OK) != -1)
		return (ft_strdup(cmd->filename));
	while (path[i])
	{
		full_cmd = ft_strjoin(path[i], cmd->filename);
		if (access(full_cmd, F_OK | X_OK) != -1)
			break ;
		free(full_cmd);
		full_cmd = 0;
		i++;
	}
	if (full_cmd == 0)
		return (ft_strdup(cmd->filename));
	return (full_cmd);
}

// 노드 type cmd일때. 처음 커맨드는 명령어로, 이후는 매개변수로 저장
int	get_cmd(t_node *node, t_cmd *cmd, char **path)
{
	if (!cmd->filename)
	{
		cmd->filename = node->str;
		cmd->filename = get_full_cmd(cmd, path, node);
	}
	if (!cmd->argv)
		cmd->argv = new_argv(node->str);
	else
		cmd->argv = join_argv(cmd->argv, node->str);
	if (node->type >= CMD_BT_PWD)
		cmd->builtin = node->type;
	return (0);
}

//실행할 커맨드의 변수(execve 2번째 매개변수) 설정 (2개이상)
char	**join_argv(char **argv, char *str)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i] = str;
	new_argv[i + 1] = 0;
	free(argv);
	return (new_argv);
}

//실행할 커맨드의 변수(execve 2번째 매개변수) 설정 (1개)
char	**new_argv(char *str)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	argv[0] = str;
	argv[1] = 0;
	return (argv);
}
