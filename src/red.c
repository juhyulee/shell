/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:10:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 14:50:57 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_red_type(char *line)
{
	if (line[0] == line[1])
	{
		if (*line == '<')
			return (RED_HEREDOC);
		else
			return (RED_APPEND);
	}
	else
	{
		if (*line == '<')
			return (RED_INFILE);
		else
			return (RED_OUTFILE);
	}
}

int	new_node_red(t_node *prev, char *line)
{
	t_node	*node;
	int		len;

	len = 1;
	while (line[len] && is_red(line[len]))
		len++;
	if (len > 2)
		return (throw_error("msh: syntax error near unexpected token \'", \
				line + len - 1, "\'", -1));
	node = init_node_node(prev);
	node->type = get_red_type(line);
	node->str = ft_strndup(line, len);
	return (len - 1);
}
