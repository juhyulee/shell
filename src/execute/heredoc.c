/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/27 12:08:10 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*heredoc_middle_inside(char *str, char *start, char *value, int val_len)
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
	len += end_len;
	temp = ft_calloc(len + 1, 1);
	ft_strlcat(temp, str, start - str + 1);
	ft_strlcat(temp, value, len);
	ft_strlcat(temp, str + start_len + val_len, len);
	return (temp);
}

char	*heredoc_str(int status, char *start, char *argv)
{
	char	*stat_str;

	stat_str = ft_itoa(status);
	start = heredoc_middle_inside(argv, start, stat_str, ft_strlen(stat_str));
	free(stat_str);
	return (start);
}

char	*heredoc_change_env(char *argv, t_env *env, int status)
{
	char	*start;
	int		key_len;

	start = ft_strrchr(argv, '$');
	if (!start)
		return (0);
	if (start && start[1] == '?')
	{
		start = heredoc_str(status, start, argv);
		return (start);
	}
	while (env)
	{
		key_len = ft_env_strnstr(start + 1, env->key, ft_strlen(env->key));
		if (key_len)
		{
			start = heredoc_middle_inside(argv, start, env->val, key_len);
			return (start);
		}
		env = env->next;
	}
	return (0);
}

char	*heredoc_check_env(char *argv, t_env *env, int status)
{
	char	*temp;

	temp = argv;
	while (ft_strchr(argv, '$'))
	{
		temp = heredoc_change_env(argv, env, status);
		if (!temp)
			return (argv);
		free(argv);
		argv = temp;
	}
	return (temp);
}
