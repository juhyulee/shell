/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:14:38 by juhyulee          #+#    #+#             */
/*   Updated: 2022/11/16 19:51:16 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]))
	{
		if (end -1 < 1)
			break ;
		end--;
	}
	if (start > end)
		return (ft_strdup(""));
	new = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s1 + start, end - start + 1);
	return (new);
}
