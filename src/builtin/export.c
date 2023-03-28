/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 14:12:31 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_env	*export_check_env(char *str, t_env *env)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	while (env)
	{
		if (!ft_strncmp(str, env->key, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	env_replace(char *str, t_env *env)
{
	int	len;

	len = 0;
	free(env->val);
	while (str[len] && str[len] != '=')
		len++;
	env->val = ft_strdup(str + len + 1);
	return (0);
}

static int	test_valid_env(char *str)
{
	if (ft_strchr(str, '='))
		return (0);
	if (ft_isalpha(str[0]))
	{
		return (1);
	}
	return (1);
}

//ok
int	builtin_export(char **argv, t_env *env)
{
	int		i;
	t_env	*temp;

	i = 1;
	while (argv[i])
	{
		if (test_valid_env(argv[i]))
		{
			return (throw_error("export: not an identifier: ", \
					argv[i], "", 1));
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		temp = export_check_env(argv[i], env);
		if (temp)
			env_replace(argv[i], temp);
		else
			env_back(argv[i], &env);
		i++;
	}
	return (0);
}
