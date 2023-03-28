/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2023/02/24 21:22:19 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	toward_c(char *str, char c)
{
	int		len;

	len = 0;
	while (*str != c && *str)
	{
		len++;
		str++;
	}
	return (len);
}

static void	free_all(char **re)
{
	int	i;

	i = 0;
	while (re[i] != 0)
	{
		free(re[i]);
		i++;
	}
	free(re);
}

static int	get_total_cnt(char *s, char c)
{
	int	len;
	int	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		len = toward_c(s, c);
		if (len)
		{
			cnt++;
			s += len;
		}
		if (*s == '\0')
			break ;
	}
	return (cnt);
}

static int	new_word(char **res, char *s, char c, char replace_char)
{
	int	len;

	while (*s == c && *s)
		s++;
	len = toward_c(s, c);
	if (!len)
		return (0);
	*res = (char *)malloc(sizeof(char) * (len + 2));
	if (!res)
		return (0);
	ft_strlcpy(*res, s, len + 1);
	(*res)[len] = replace_char;
	(*res)[len + 1] = 0;
	return (len);
}

char	**ft_split_replace(char const *s, char c, char replace_char)
{
	int		cnt;
	int		i;
	int		total_cnt;
	char	**res;

	total_cnt = get_total_cnt((char *)s, c);
	res = malloc(sizeof(char *) * (total_cnt + 1));
	if (!res)
		return (0);
	cnt = -1;
	i = 0;
	while (++cnt < total_cnt)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		i += new_word(res + cnt, (char *)s + i, c, replace_char) + 1;
		if (!res[cnt])
		{
			free_all(res);
			return (0);
		}
	}
	res[total_cnt] = 0;
	return (res);
}
