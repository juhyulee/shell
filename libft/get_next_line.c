/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:25:35 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/17 18:24:17 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_substr(char *s, unsigned int start)
{
	char	*sub;
	size_t	i;
	size_t	j;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	while (s[j])
		j++;
	sub = (char *)malloc((j + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[start])
		sub[i++] = s[start++];
	sub[i] = 0;
	free(s);
	return (sub);
}

size_t	gnl_nlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s && s[c] != '\n' && s[c])
		c++;
	return (c);
}

char	*gnl_readline(int fd, char *store)
{
	char	*buf;
	int		byte;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!gnl_strchr(store, '\n'))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == 0)
			break ;
		if (byte == -1)
		{
			free(buf);
			free(store);
			store = 0;
			return (NULL);
		}
		buf[byte] = 0;
		store = gnl_strjoin(store, buf);
	}
	free(buf);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*retline;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	store = gnl_readline(fd, store);
	if (!store)
		return (0);
	len = gnl_nlen(store);
	retline = gnl_strdup(store, len);
	if (store[len] != 0 && store[len + 1] != 0)
		store = gnl_substr(store, len + 1);
	else
	{
		free(store);
		store = 0;
	}
	return (retline);
}
