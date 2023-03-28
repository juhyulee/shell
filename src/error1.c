/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:08:22 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 14:16:47 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parse_error_red(char *line)
{
	if (!ft_strncmp(">>>", line, 3))
		return (1);
	if (!ft_strncmp("<<<", line, 3))
		return (1);
	return (0);
}

int	error_parsing_final_check(t_error *err)
{
	if (err->pipe != 0)
		return (throw_error("msh: ", "end pipe", "", 1));
	if (err->quote != 0)
		return (throw_error("msh: ", "quote unclosed", "", 1));
	return (0);
}

int	error_parsing(char *line)
{
	t_error	err;

	init_error_struct(&err);
	while (*line)
	{
		err.quote = check_quote(*line, err.quote);
		if (is_pipe(*line) && err.pipe == 0)
			err.pipe = 1;
		else if (!is_pipe(*line) && !is_space(*line))
		{
			err.str = 1;
			err.pipe = 0;
		}
		else if (is_pipe(*line) && err.pipe == 1)
			return (throw_error("msh: ", "", "double pipe", 1));
		if (is_pipe(*line) && err.str == 0)
			return (throw_error("msh: ", "", "start pipe", 1));
		if (is_red(*line) && check_parse_error_red(line))
			return (throw_error("msh: ", "", "msh: parse error near < >", 1));
		line++;
	}
	return (error_parsing_final_check(&err));
}
