/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 17:23:19 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

t_fd	open_read(t_string str, int flags)
{
	t_fd	file;

	file = -1;
	file = open(str, flags);
	if (file < 0)
	{
		if (!access(str, F_OK))
			wati_error("permission denied: %s", str);
		else
			wati_error("no such file or directory: %s", str);
	}
	return (file);
}
