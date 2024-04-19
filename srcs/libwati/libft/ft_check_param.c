/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:14:17 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/27 17:09:01 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_param(char *str, va_list param, int i)
{
	int	result;

	result = 0;
	if (str[i] == 'c')
		result = ft_putchar_fd(va_arg(param, int), 1);
	else if (str[i] == 's')
		result = ft_putstr_fd(va_arg(param, char *), 1);
	else if (str[i] == 'p')
		result = ft_print_adress(va_arg(param, unsigned long long), \
		"0123456789abcdef", 16);
	else if (str[i] == 'd' || str[i] == 'i')
		result = ft_putnbr_base(va_arg(param, int), "", 10);
	else if (str[i] == 'u')
		result = ft_putnbr_base(va_arg(param, unsigned int), "", 10);
	else if (str[i] == 'x')
		result = ft_putnbr_base(va_arg(param, unsigned int), \
		"0123456789abcdef", 16);
	else if (str[i] == 'X')
		result = ft_putnbr_base(va_arg(param, unsigned int), \
		"0123456789ABCDEF", 16);
	else if (str[i] == '%')
		result = ft_putchar_fd('%', 1);
	return (result);
}
