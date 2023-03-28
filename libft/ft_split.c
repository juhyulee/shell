/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:07:25 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/06 21:32:33 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	allo(char const *str, char c)
{
	int	size;
	int	i;
	int	flag;

	size = 0;
	i = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] != c && flag == 1)
		{
			size += 1;
			flag = 0;
		}
		if (str[i] == c && flag == 0)
			flag = 1;
		i++;
	}
	return (size);
}

static char	**allo2(char **res, char const *str, char c, int wordcnt)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (k < wordcnt)
	{
		if (*str == c)
			str++;
		if (*str != c)
		{
			while (*str != c && *str)
			{
				res[k][i] = *str;
				i++;
				str++;
			}
			res[k][i] = 0;
			k++;
			i = 0;
		}
	}
	res[k] = 0;
	return (res);
}

static char	**allofree(int i, char **res)
{
	while (--i >= 0)
		if (res[i] == 0)
			free(res[i]);
	return ((char **)ft_strdup(""));
}

static char	**allo3(char **res, char const *str, char c, int wordcnt)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < wordcnt)
	{
		if (*str == c)
			str++;
		if (*str != c)
		{
			while (*str != c && *str)
			{
				i++;
				str++;
			}
			res[j] = (char *)malloc(sizeof(char) * (i + 1));
			if (!res[j])
				res = allofree(j, res);
			j++;
			i = 0;
		}
	}
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		wordcnt;

	wordcnt = allo(str, c);
	res = (char **)malloc(sizeof(char *) * (wordcnt + 1));
	if (!res)
		return (0);
	res = allo3(res, str, c, wordcnt);
	if (res != 0)
		res = allo2(res, str, c, wordcnt);
	return (res);
}
