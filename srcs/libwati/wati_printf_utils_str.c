/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_printf_utils_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:43:48 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/19 15:58:28 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

int	wati_printf_char_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	wati_printf_str_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, wati_strlen(s)));
}
