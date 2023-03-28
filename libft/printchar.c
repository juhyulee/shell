/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:33:26 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/27 19:54:57 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int arg)
{
	int		len;
	char	c;

	len = 0;
	c = arg;
	write(1, &c, 1);
	len++;
	return (len);
}
