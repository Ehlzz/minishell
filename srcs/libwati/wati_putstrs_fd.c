/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_putstrs_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:14:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/17 11:31:10 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	wati_putstrs_fd(char **s, int fd)
{
	while (*s)
		wati_putstr_fd(*s++, fd);
}
