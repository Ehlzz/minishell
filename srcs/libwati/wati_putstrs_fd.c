/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_putstrs_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:14:29 by bedarenn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/28 17:31:17 by bedarenn         ###   ########.fr       */
=======
/*   Updated: 2024/04/19 20:47:58 by ehalliez         ###   ########.fr       */
>>>>>>> ehalliez
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	wati_putstrs_fd(char **s, int fd)
{
	while (*s)
<<<<<<< HEAD
		wati_putendl_fd(*s++, fd);
=======
	{
		wati_putstr_fd(*s++, fd);
		wati_putchar_fd('\n', fd);
	}
>>>>>>> ehalliez
}
