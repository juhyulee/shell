/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:27:50 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 16:23:43 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char line, int quote)
{
	int	flag;

	flag = quote;
	if (line == '\'')
	{
		if (quote == 1)
			flag = 0;
		else if (quote == 2)
			flag = 2;
		else
			flag = 1;
	}
	else if (line == '\"')
	{
		if (quote == 2)
			flag = 0;
		else if (quote == 1)
			flag = 1;
		else
			flag = 2;
	}
	return (flag);
}

char	*ft_strndup(char *s, int i)
{
	char	*t;

	t = malloc((i + 1));
	if (t == 0)
		return (0);
	if (s == 0)
		return (0);
	ft_memcpy(t, s, i);
	t[i] = 0;
	return (t);
}

void	free_node(t_node *head)
{
	t_node	*temp;
	t_node	*node;

	node = head->next;
	while (node)
	{
		temp = node->next;
		free(node->str);
		node->str = 0;
		free(node);
		node = 0;
		node = temp;
	}
	head->next = 0;
}

int	ft_env_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	alen;

	i = 0;
	alen = (int)ft_strlen(needle);
	if (*needle == 0)
		return (0);
	if ((int)ft_strlen(haystack) < alen)
		return (0);
	while (i < alen)
	{
		if (haystack[i] == needle[0])
		{
			if (len - i >= alen)
			{
				if (ft_strncmp(haystack + i, needle, alen) == 0)
				{
					return (alen);
				}
			}
		}
		i++;
	}
	return (0);
}
