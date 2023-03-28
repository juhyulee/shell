/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:07:58 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 20:03:36 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	built_cmp(char *line)
{
	if (!ft_strcmp(line, "echo"))
		return (CMD_BT_ECHO);
	else if (!ft_strcmp(line, "cd"))
		return (CMD_BT_CD);
	else if (!ft_strcmp(line, "env"))
		return (CMD_BT_ENV);
	else if (!ft_strcmp(line, "exit") || !ft_strcmp(line, "quit"))
		return (CMD_BT_EXIT);
	else if (!ft_strcmp(line, "export"))
		return (CMD_BT_EXPORT);
	else if (!ft_strcmp(line, "pwd"))
		return (CMD_BT_PWD);
	else if (!ft_strcmp(line, "unset"))
		return (CMD_BT_UNSET);
	else
		return (CMD);
}

int	parse_type(t_node *node, char *line, int i)
{
	static int	red_chk;
	int			chk;

	if (is_space(line[i]))
		return (new_node_empty(node, line + i));
	else if (is_quote(line[i]))
		return (new_node_quote(node, line + i));
	else if (is_pipe(line[i]))
		return (new_node_pipe(node));
	else if (is_red(line[i]))
	{
		chk = new_node_red(node, line + i);
		if (chk != -1)
			red_chk = 1;
		return (chk);
	}
	else if (red_chk)
	{
		red_chk = 0;
		return (new_node_eof(node, line + i));
	}
	else
		return (new_node_node(node, line + i));
}

int	parse(char *line, t_node **head)
{
	int		i;
	int		chk;
	t_node	*node;
	int		red_chk;

	node = *head;
	i = -1;
	red_chk = 0;
	while (line[++i])
	{
		chk = parse_type(node, line, i);
		if (chk == -1)
			return (-1);
		i += chk;
		node = node->next;
		if (node->type && node->type < RED)
			red_chk = 1;
		if (red_chk && node->type == RED)
			red_chk = 0;
	}
	if (red_chk)
		return (throw_error("msh: ", "", "parse error near redirection", -1));
	return (0);
}
