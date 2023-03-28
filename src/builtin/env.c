/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 14:12:26 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//일단되긴함... 매개변수는 ? 안함..
int	builtin_env(char **argv, t_env *env)
{
	if (!env)
		return (1);
	if (argv[1])
		return (throw_error("env: ", argv[1], "No Such file or directory", 1));
	if (argv[1] && argv[2])
		return (throw_error("env: permission denied", "", "", 1));
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->val, 1);
		env = env->next;
	}
	return (0);
}
