/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:26:54 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 18:47:38 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen((char *)s1);
	l2 = ft_strlen((char *)s2);
	if (!l1 && !l2)
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!p)
		exit(1);
	ft_strlcpy(p, s1, l1 + 1);
	ft_strlcpy(p + l1, s2, l2 + 1);
	return (p);
}
