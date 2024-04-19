/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:19:03 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/27 16:25:43 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_adress(unsigned long long int nb, \
char *hex, unsigned long long int base)
{
	char	unit;
	int		count;

	count = 1;
	if (!nb)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (base == 16)
	{
		write(1, "0x", 2);
		unit = hex[nb % 16];
		count += 2;
	}
	else if (base == 10)
	{
		unit = nb % base;
		unit = unit + '0';
	}
	if (nb > base - 1)
		count += ft_putnbr_base(nb / base, hex, base);
	write(1, &unit, 1);
	return (count);
}
