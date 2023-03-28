/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:09:43 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 18:43:01 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_node_empty(t_node *prev, char *line)
{
	int		len;
	t_node	*node;

	len = 1;
	while (is_space(*(line + len)))
	{
		len++;
	}
	node = init_node_node(prev);
	node->type = EMPTY;
	return (len - 1);
}

int	new_node_quote(t_node *prev, char *line)
{
	int		len;
	t_node	*node;

	len = 1;
	while (line[len] && line[len] != *line)
		len++;
	if (line[len] != *line)
		return (-1);
	node = init_node_node(prev);
	node->type = CMD;
	node->str = ft_strndup(line, len + 1);
	return (len);
}

int	new_node_pipe(t_node *prev)
{
	t_node	*node;

	node = init_node_node(prev);
	node->type = PIP;
	node->str = ft_strdup("|");
	return (0);
}

int	new_node_node(t_node *prev, char *line)
{
	int		len;
	t_node	*node;

	len = 1;
	while (!is_space(line[len]) && line[len] && \
			!is_pipe(line[len]) && !is_quote(line[len]) && !is_red(line[len]))
		len++;
	node = init_node_node(prev);
	node->str = ft_strndup(line, len);
	node->type = built_cmp(node->str);
	return (len - 1);
}

int	new_node_eof(t_node *prev, char *line)
{
	int		len;
	t_node	*node;

	len = 1;
	while (!is_space(line[len]) && line[len] && !is_pipe(line[len])
		&& !is_quote(line[len]))
		len++;
	node = init_node_node(prev);
	node->type = RED;
	node->str = ft_strndup(line, len);
	return (len - 1);
}
