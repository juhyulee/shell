/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:16:22 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 18:28:15 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_var(char *const *envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] && ft_strncmp(envp[i], var, len))
	{
		i++;
	}
	if (envp[i] == 0)
		return (NULL);
	return (envp[i] + len + 1);
}

char	**get_path(t_env *env)
{
	while (env && env->key && ft_strncmp(env->key, "PATH", 4))
	{
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_split_replace(env->val, ':', '/'));
}

t_cmd	*init_cmd(t_env *env, int status)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = 0;
	cmd->filename = 0;
	cmd->inpipe = 0;
	cmd->outpipe = 0;
	cmd->builtin = 0;
	cmd->cnt = 0;
	cmd->red_file = 0;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->status = status;
	cmd->path = get_path(env);
	dup2(STDOUT_FILENO, STDOUT_BU);
	dup2(STDIN_FILENO, STDIN_BU);
	return (cmd);
}

void	mini_lstclear(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (lst)
	{
		temp = (lst)->next;
		unlink((lst)->content);
		free((lst)->content);
		free(lst);
		lst = temp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd);
	dup2(STDOUT_BU, 1);
	dup2(STDIN_BU, 0);
}
