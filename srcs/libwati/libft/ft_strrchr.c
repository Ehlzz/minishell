/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:47:52 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 18:07:04 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen((char *) str);
	while (*str)
		str++;
	while (i < size + 1)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str--;
		size--;
	}
	if (c == 0)
		return ((char *) str);
	return (0);
}
