/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:30:10 by juhyulee          #+#    #+#             */
/*   Updated: 2022/12/14 19:02:12 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*b;
	char		t;
	size_t		i;

	t = c;
	b = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (b[i] == t)
			return ((void *)b + i);
		i++;
	}
	return (NULL);
}
