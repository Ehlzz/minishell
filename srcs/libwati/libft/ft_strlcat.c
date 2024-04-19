/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:17:16 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 22:07:15 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_dest;
	size_t	size_src;

	if ((!dest || !src) && size == 0)
		return (0);
	i = 0;
	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	if (size > size_dest)
	{
		while (src && src[i] && (i + size_dest < size - 1))
		{
			dest[i + size_dest] = src[i];
			i++;
		}
		dest[i + size_dest] = '\0';
		return (size_dest + size_src);
	}
	return (size_src + size);
}
