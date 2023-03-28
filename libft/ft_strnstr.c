/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:02:34 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/15 14:35:49 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	if (ft_strlen(haystack) < ft_strlen(needle))
		return (0);
	while (i < len)
	{
		if (haystack[i] == needle[0])
		{
			if (len - i >= ft_strlen(needle))
			{
				if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (0);
}
