/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:33:54 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/27 17:09:03 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(long long int nb, char *hex, long long int base)
{
	char	unit;
	int		count;

	count = 1;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
		count++;
	}
	if (base == 16)
		unit = hex[nb % 16];
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
