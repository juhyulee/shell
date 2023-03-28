/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:06:28 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/19 20:11:28 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recur(int nb, int fd)
{
	char	mod;

	if (nb == 0)
		return ;
	recur(nb / 10, fd);
	mod = nb % 10 + 48;
	write(fd, &mod, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		recur(-n, fd);
	}
	else if (n > 0)
		recur(n, fd);
	else if (n == 0)
		write(fd, "0", 1);
}
