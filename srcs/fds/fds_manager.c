/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 12:29:41 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wati_struct.h"
#include <unistd.h>

void	close_fds(t_fds fds)
{
	if (fds.in > 2)
		close(fds.in);
	if (fds.out > 2)
		close(fds.out);
}
