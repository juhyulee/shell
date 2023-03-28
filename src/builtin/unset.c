/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 19:57:40 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *env)
{
	free(env->key);
	free(env->val);
	free(env);
}

static int	unset_env(t_env **env, char *str)
{
	t_env	*prev;
	t_env	*now;

	prev = *env;
	if (!ft_strcmp(str, prev->key))
	{
		*env = prev->next;
		free_env(prev);
		return (0);
	}
	now = *env;
	while (now->next)
	{
		prev = now;
		now = now->next;
		if (!ft_strcmp(str, now->key))
		{
			prev->next = now->next;
			free_env(now);
			return (0);
		}
	}
	return (1);
}

//unset ok
int	builtin_unset(char **argv, t_env *env)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		return (unset_env(&env, argv[i]));
		i++;
	}
	return (1);
}
