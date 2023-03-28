/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:48 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/26 15:59:07 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	exit_error(char *str)
{
	child_exit("exit : ", str, ": numeric argument required", 255);
}

static void	exit_isnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && !(is_space(str[i])) && str[i] != '+'
			&& str[i] != '-')
			exit_error(str);
	}
}

static int	exit_atoi(char *str)
{
	int		ans;
	int		sign;
	char	*bu;
	int		i;

	ans = 0;
	sign = 1;
	bu = (char *)str;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	if (ans * sign < 0 || ans * sign > 255 || str[i])
		exit_error(bu);
	return ((int)(ans * sign));
}

int	builtin_exit(char **argv)
{
	int	code;

	if (argv[1] && argv[2])
		child_exit("exit: too many arguments", "", "", 1);
	if (argv[1])
	{
		exit_isnum(argv[1]);
		code = exit_atoi(argv[1]);
		exit(code);
	}
	ft_putendl_fd("exit", 1);
	exit(0);
}
