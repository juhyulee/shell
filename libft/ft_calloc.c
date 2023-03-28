/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:27:30 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/13 13:43:27 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*myreturn;

	if (size > 0 && count > SIZE_MAX / size)
		return (0);
	myreturn = malloc(size * count);
	if (!myreturn)
		return (0);
	ft_bzero(myreturn, size * count);
	return ((void *)myreturn);
}
