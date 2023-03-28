/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmodule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:11:36 by juhyulee          #+#    #+#             */
/*   Updated: 2023/01/27 19:55:12 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_type(char format, va_list lst)
{
	int	len;

	len = 0;
	if (format == 'c')
		len = print_char(va_arg(lst, int));
	else if (format == 's')
		len = print_str(va_arg(lst, char *));
	else if (format == 'p')
		len = print_ptr(va_arg(lst, size_t));
	else if (format == 'd')
		len = print_dec(va_arg(lst, int));
	else if (format == 'i')
		len = print_int(va_arg(lst, int));
	else if (format == 'u')
		len = print_un_dec(va_arg(lst, unsigned int));
	else if (format == 'x')
		len = printhex_low(va_arg(lst, unsigned int));
	else if (format == 'X')
		len = printhex_upp(va_arg(lst, unsigned int));
	else if (format == '%')
		len += write(1, "%", 1);
	return (len);
}
