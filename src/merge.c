/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:34:32 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 19:46:59 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_cmd_sub(t_node *node, t_node *head, char *s1)
{
	char	*temp;

	temp = ft_strjoin(node->str, s1);
	free(node->str);
	node->str = temp;
	node->type = CMD;
	node->next = head;
}

void	merge_cmd(t_node *head)
{
	char	*str;
	t_node	*node;
	t_node	*temp;

	while (head)
	{
		str = ft_strdup("");
		head = head->next;
		if (head && head->type >= CMD && head->type <= CMD_DQ)
		{
			node = head;
			head = head->next;
			while (head && head->type >= CMD && head->type <= CMD_DQ)
			{
				str = ft_strjoin(str, head->str);
				temp = head->next;
				free(head->str);
				free(head);
				head = temp;
			}
			merge_cmd_sub(node, head, str);
		}
		free(str);
	}
}
