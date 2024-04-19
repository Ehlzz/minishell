/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:52:02 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/08 06:33:33 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	unit;

	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	unit = nb % 10;
	unit = unit + '0';
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	write(fd, &unit, 1);
}
