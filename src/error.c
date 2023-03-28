/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:50:41 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 14:17:14 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error_struct(t_error *error)
{
	error->pipe = 0;
	error->str = 0;
	error->quote = 0;
}

int	throw_error(char *mes1, char *mes2, char *mes3, int code)
{
	ft_putstr_fd("\033[31m\033[9m", 2);
	ft_putstr_fd(mes1, 2);
	ft_putstr_fd(mes2, 2);
	ft_putendl_fd(mes3, 2);
	ft_putstr_fd("\033[0m", 2);
	return (code);
}
