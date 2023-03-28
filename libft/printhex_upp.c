/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex_upp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:44:55 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/27 19:55:07 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(size_t n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

char	*ft_itoa_upp(size_t n)
{
	char		*res;
	size_t		len;
	size_t		m;
	char const	*hex;

	hex = "0123456789ABCDEF";
	if (n == 0)
	{
		res = (char *)malloc(sizeof(char) * (2));
		res[0] = '0';
		res[1] = 0;
		return (res);
	}
	m = n;
	len = nlen(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	while (m)
	{
		res[--len] = hex[m % 16];
		m = m / 16;
	}
	return (res);
}

int	printhex_upp(unsigned int arg)
{
	int		len;
	char	*s;
	int		i;

	len = 0;
	i = 0;
	s = ft_itoa_upp(arg);
	if (!s)
		return (0);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
		len++;
	}
	free(s);
	return (len);
}
