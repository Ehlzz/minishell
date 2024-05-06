/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/03 12:45:12 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

t_bool	open_read(t_fds *fds, t_string str, int flags)
{
	wati_close(fds->in);
	fds->in = -1;
	fds->in = open(str, flags);
	if (fds->in < 0)
	{
		if (!access(str, F_OK))
			return (wati_error("permission denied: %s", str));
		return (wati_error("no such file or directory: %s", str));
	}
	free(str);
	return (TRUE);
}
