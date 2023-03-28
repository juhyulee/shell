/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:30:05 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/23 22:05:06 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_val(char *str)
{
	int	i;

	if (!ft_strchr(str, '='))
		return (0);
	i = 0;
	while (str[i] != '=')
		i++;
	return (ft_strdup(str + i + 1));
}

void	env_back(char *str, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	node = *env;
	while (node->next)
		node = node->next;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!(tmp))
		printf("error at env_back\n");
	tmp->key = get_key(str);
	tmp->val = get_val(str);
	tmp->next = 0;
	node->next = tmp;
}

void	make_env(char **envp, t_env **env)
{
	int	i;

	if (!*env)
	{
		*env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			printf("error at make_env");
		(*env)->key = get_key(envp[0]);
		(*env)->val = get_val(envp[0]);
		(*env)->next = NULL;
	}
	i = 0;
	while (envp[++i])
		env_back(envp[i], env);
}
