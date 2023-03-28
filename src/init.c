/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:31:53 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/23 22:08:41 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_head(t_node **head)
{
	*head = (t_node *)malloc(sizeof(t_node));
	(*head)->str = ft_strdup("node 0");
	(*head)->type = 0;
	(*head)->next = NULL;
}

void	main_init(int ac, char **envp, t_env **env, t_node **head)
{
	struct termios	term;

	*env = 0;
	if (ac != 1)
		printf("ac error");
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	init_head(head);
	make_env(envp, env);
}

t_node	*init_node_node(t_node *head)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->str = 0;
	node->type = 0;
	node->next = 0;
	head->next = node;
	return (node);
}
