/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 02:21:01 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/08 03:32:29 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	size = ft_strlen((char *)to_find);
	if (len == 0 && size != 0)
		return (0);
	if ((len == 0 || size == 0))
		return ((char *)&str[i]);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (j == size - 1)
				return ((char *)&str[i]);
			j++;
			if (i + j == len)
				return (0);
		}
		i++;
	}
	return (0);
}
