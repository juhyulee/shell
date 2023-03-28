/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_un_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:44:30 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/27 19:54:51 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_un(unsigned int n)
{
	char			*res;
	int				len;
	unsigned int	m;

	m = n;
	len = nlen(m);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	if (n == 0)
		res[0] = 48;
	while (m)
	{
		res[--len] = (m % 10) + '0';
		m = m / 10;
	}
	return (res);
}

int	print_un_dec(unsigned int arg)
{
	int		len;
	char	*s;
	int		i;

	len = 0;
	i = 0;
	s = ft_itoa_un(arg);
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
