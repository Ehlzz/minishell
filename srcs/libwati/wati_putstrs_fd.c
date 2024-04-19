/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_putstrs_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:14:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/19 20:47:58 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	wati_putstrs_fd(char **s, int fd)
{
	while (*s)
	{
		wati_putstr_fd(*s++, fd);
		wati_putchar_fd('\n', fd);
	}
}
