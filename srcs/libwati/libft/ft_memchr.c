/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 04:05:48 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 22:06:46 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( const void *str, int c, size_t size)
{
	size_t			i;
	unsigned char	*c_str;

	if (size == 0)
		return (0);
	c_str = (unsigned char *)str;
	i = 0;
	while (i < size)
	{
		if (c_str [i] == (unsigned char)c)
			return (&c_str [i]);
		i++;
	}
	if (c == 0)
		return (c_str);
	return (0);
}
