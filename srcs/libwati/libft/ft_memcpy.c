/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:32:23 by ehalliez          #+#    #+#             */
/*   Updated: 2023/12/18 05:22:51 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	long			*d;
	const long		*s;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (long *)dest;
	s = (const long *)src;
	while (i < n / sizeof(long))
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
