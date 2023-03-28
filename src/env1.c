/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:14:26 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/23 22:08:15 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*middle_inside(char *str, char *start, char *value, int val_len)
{
	char	*temp;
	int		len;
	int		start_len;
	int		mid_len;
	int		end_len;

	start_len = start - str + 1;
	len = start_len;
	mid_len = ft_strlen(value);
	len += mid_len;
	end_len = ft_strlen(str) - val_len - start_len;
	if (end_len > 0)
		len += end_len;
	temp = ft_calloc(len + 1, 1);
	ft_strlcat(temp, str, start - str + 1);
	ft_strlcat(temp, value, len);
	ft_strlcat(temp, str + start_len + val_len, len);
	return (temp);
}

char	*change_env_sub(int status, char *start, t_node *head)
{
	char	*stat_str;
	char	*new_str;

	stat_str = ft_itoa(status);
	new_str = middle_inside(head->str, start, \
	stat_str, ft_strlen(stat_str));
	free(head->str);
	free(stat_str);
	head->str = new_str;
	return (start);
}

char	*change_env_dq(char *start, t_node *head, t_env *env)
{
	int		key_len;
	char	*new_str;

	new_str = 0;
	while (env)
	{
		key_len = ft_env_strnstr(start + 1, env->key, ft_strlen(env->key));
		if (key_len)
		{
			new_str = middle_inside(head->str, start, env->val, key_len);
			free(head->str);
			break ;
		}
		env = env->next;
	}
	return (new_str);
}

int	change_env(t_node *head, t_env *env, int status)
{
	char	*start;

	start = ft_strrchr(head->str, '$');
	if (!start)
		return (0);
	if (start && start[1] == '?')
	{
		start = change_env_sub(status, start, head);
		return (0);
	}
	if (start && head->type != CMD_SQ)
	{
		head->str = change_env_dq(start, head, env);
		return (0);
	}
	return (1);
}

void	check_lst_env(t_node *head, t_env *env, int status)
{
	head = head->next;
	while (head)
	{
		while (head->type != CMD_SQ && ft_strchr(head->str, '$'))
		{
			if (change_env(head, env, status))
				break ;
		}
		head = head->next;
	}
}
