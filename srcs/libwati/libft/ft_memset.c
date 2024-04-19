/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:17:26 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/07 19:15:45 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t		i;
	char		*c;

	i = 0;
	c = (char *)pointer;
	while (i < count)
	{
		c[i] = value;
		i++;
	}
	return (pointer);
}
