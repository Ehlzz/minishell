/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:19:38 by ehalliez          #+#    #+#             */
/*   Updated: 2023/12/19 20:03:37 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	result_atoi(int i, int neg, int pos, char *nb)
{
	int	number;

	number = 0;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		number = number * 10 + nb[i] - '0';
		i++;
	}
	if (neg > 0 && pos > 0)
		return (0);
	if (neg == 1)
		return (-number);
	if (pos == 1)
		return (number);
	if (pos == 0 && neg == 0)
		return (number);
	return (0);
}

int	ft_strlen_to_eleven(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i >= 11)
			return (0);
		i++;
	}
	return (1);
}

int	check_overflow(char *nb, int pos, int neg)
{
	if (!ft_strlen_to_eleven(nb))
		return (1);
	if (pos == 1 && ft_strlen(nb) == 10 && \
	ft_strncmp(nb, "2147483647", 10) >= 1)
		return (1);
	if (neg == 1 && ft_strlen(nb) == 11 && \
	ft_strncmp(nb, "-2147483648", 11) >= 1)
		return (1);
	return (0);
}

long	ft_atoi(const char *nb)
{
	int		i;
	int		pos;
	int		neg;
	long	number;

	i = 0;
	neg = 0;
	pos = 0;
	while ((nb[i] >= 7 && nb[i] <= 13) || nb[i] == ' ')
		i++;
	while (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			neg++;
		if (nb[i] == '+')
			pos++;
		i++;
	}
	if (check_overflow(((char *)nb), pos, neg))
		return (2147483648);
	number = result_atoi(i, neg, pos, (char *)nb);
	return (number);
}
