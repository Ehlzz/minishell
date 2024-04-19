/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 05:18:36 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/08 06:35:04 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_result(int nb, int i, int size, char *result)
{
	while (size > i)
	{
		result[size - 1] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
}

static	int	size_nb(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		range;
	int		size;

	range = 0;
	size = size_nb(nb);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (0);
	if (nb == -2147483648)
	{
		result[0] = '-';
		result[1] = '2';
		nb = 147483648;
		range = 2;
	}
	if (nb < 0)
	{
		result[0] = '-';
		range = 1;
		nb = -nb;
	}
	set_result(nb, range, size, result);
	result[size] = 0;
	return (result);
}
