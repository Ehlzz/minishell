/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_putstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:30:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/17 11:31:11 by bedarenn         ###   ########.fr       */
=======
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:30:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/12 14:04:40 by ehalliez         ###   ########.fr       */
>>>>>>> ehalliez
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <unistd.h>

void	wati_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, wati_strlen(s));
}
