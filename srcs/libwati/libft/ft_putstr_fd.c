/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 05:05:51 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/30 16:49:10 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (ft_strlen(str));
}
