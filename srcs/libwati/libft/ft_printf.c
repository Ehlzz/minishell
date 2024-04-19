/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:43:41 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/27 17:04:50 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	param;
	int		test;
	int		i;

	i = 0;
	test = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			test += ft_check_param((char *)str, param, i + 1);
			i += 1;
		}
		else
			test += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(param);
	return (test);
}
