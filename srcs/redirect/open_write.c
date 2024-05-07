/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:40 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:47:00 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

t_fd	open_write(t_string str, int flags)
{
	t_fd	file;

	file = -1;
	file = open(str, flags, 0644);
	if (file < 0)
		return (wati_error("permission denied: %s", str));
	return (file);
}
