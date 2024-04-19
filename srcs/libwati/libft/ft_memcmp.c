/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:33:53 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/08 04:03:59 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	size_t			i;
	unsigned char	*f_p;
	unsigned char	*s_p;

	i = 0;
	f_p = (unsigned char *)p1;
	s_p = (unsigned char *)p2;
	while (i < size)
	{
		if (f_p[i] < s_p[i])
			return (f_p[i] - s_p[i]);
		if (f_p[i] > s_p[i])
			return (f_p[i] - s_p[i]);
		i++;
	}
	return (0);
}
