/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 20:05:00 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//pwd 있는 env 리턴
static t_env	*get_pwd_where(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp("PWD", env->key))
			return (env);
		env = env->next;
	}
	return (0);
}

//상위폴더 path 리턴
char	*get_up_dir(char *pwd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			len = i;
		i++;
	}
	return (ft_strndup(pwd, len));
}

//하위폴더 path 리턴
char	*get_down_dir(char *pwd, char *dir)
{
	char	*path;

	pwd = ft_strjoin(pwd, "/");
	path = ft_strjoin(pwd, dir);
	free(pwd);
	return (path);
}

int	cd_error(char *path, char *str)
{
	free(path);
	return (throw_error("msh: no such file or directory:", str, "", 1));
}

//cd ->pwd
//../이런 식으로 이동 안됨 ㅎㅎ
//일단 ok
int	builtin_cd(char **argv, t_env *env)
{
	t_env	*pwd;
	char	*path;

	if (argv[1] && argv[2] != 0)
		throw_error("msh: ", "string not in pwd: ", argv[1], 1);
	pwd = get_pwd_where(env);
	if (!argv[1])
		path = get_env_value(env, "HOME");
	else if (argv[1] && !ft_strcmp(argv[1], "."))
		return (0);
	else if (!pwd)
		return (throw_error("msh: no pwd", "", "", 1));
	else if (!ft_strcmp(argv[1], ".."))
		path = get_up_dir(pwd->val);
	else if (argv[1][0] == '/')
		path = ft_strdup(argv[1]);
	else
		path = get_down_dir(pwd->val, argv[1]);
	if (access(path, F_OK) == -1 || chdir((path)) == -1)
		return (cd_error(path, argv[1]));
	free(pwd->val);
	pwd->val = path;
	return (0);
}
