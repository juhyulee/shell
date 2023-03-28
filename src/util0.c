/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:27:43 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/25 18:04:34 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else
		return (0);
}

char	*ft_charjoin(char *s1, char s2)
{
	char	*ret;
	size_t	len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (len + 2));
	ft_strlcpy(ret, s1, len + 1);
	ft_strlcpy(ret + len, &s2, 2);
	free(s1);
	return (ret);
}

void	del_single_quote(t_node *head)
{
	char	*temp;
	int		i;

	temp = ft_strdup("");
	head->type = CMD_SQ;
	i = 0;
	while (head->str[i])
	{
		if (head->str[i] != '\'')
			temp = ft_charjoin(temp, head->str[i]);
		i++;
	}
	head->str = temp;
}

void	del_double_quote(t_node *head)
{
	char	*temp;
	int		i;

	temp = ft_strdup("");
	head->type = CMD_DQ;
	i = 0;
	while (head->str[i])
	{
		if (head->str[i] != '\"')
			temp = ft_charjoin(temp, head->str[i]);
		i++;
	}
	head->str = temp;
}

void	check_quote_lst(t_node *head)
{
	head = head->next;
	while (head)
	{
		while (head && !head->str)
			head = head->next;
		if (!head)
			break ;
		if (head->str[0] == '\'')
			del_single_quote(head);
		else if (head->str[0] == '\"')
			del_double_quote(head);
		head = head->next;
	}
}
