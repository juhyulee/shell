/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:30:20 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/13 18:14:25 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	t;
	char			*save;
	size_t			len;
	size_t			i;

	len = ft_strlen(s);
	t = c;
	save = 0;
	i = 0;
	while (i < len + 1)
	{
		if (*s == t)
			save = ((char *)s);
		i++;
		s++;
	}
	return (save);
}
