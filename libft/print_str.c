/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:43:29 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/27 19:54:45 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *arg)
{
	int	len;

	len = 0;
	if (!arg)
		return (write(1, "(null)", 6));
	while (*arg)
	{
		write(1, arg, 1);
		arg++;
		len++;
	}
	return (len);
}
