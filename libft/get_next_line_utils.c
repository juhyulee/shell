/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:24:12 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/17 18:23:48 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *s)
{
	int	c;

	c = 0;
	while (s[c])
	{
		c++;
	}
	return (c);
}

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	s = (unsigned char *)src;
	d = dst;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*gnl_strchr(char *s, int c)
{
	char	ch;

	ch = c;
	if (!s)
		return (0);
	while (*s != ch)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*news;
	size_t	i;
	size_t	c;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (0);
	news = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (news == 0)
		return (0);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != 0)
			news[i] = s1[i];
	while (s2[c] != 0)
		news[i++] = s2[c++];
	news[gnl_strlen(s1) + gnl_strlen(s2)] = 0;
	free(s1);
	return (news);
}

char	*gnl_strdup(char *s, size_t length)
{
	char	*t;

	t = malloc((length + 2));
	if (t == 0)
		return (0);
	if (s == 0)
		return (0);
	gnl_memcpy(t, s, length + 1);
	t[length + 1] = 0;
	return (t);
}
