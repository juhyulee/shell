/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:55:07 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/22 18:46:44 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	cnt = 0;
	j = start;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen((char *)s))
		return (ft_strdup(""));
	while (s[j] && cnt < len)
	{
		j++;
		cnt++;
	}
	sub = (char *)malloc((cnt + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[start] && i < len)
		sub[i++] = s[start++];
	sub[i] = 0;
	return (sub);
}
