/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 14:12:38 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (0);
}

//pwd ok
int	builtin_pwd(char **argv, t_env *env)
{
	char	*pwd;
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_strcmp(argv[i], "-L") || !ft_strcmp(argv[i], "-P"))
			break ;
		return (throw_error("pwd: bad option: ", argv[i], "", 1));
		i++;
	}
	pwd = get_env_value(env, "PWD");
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
