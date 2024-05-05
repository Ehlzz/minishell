/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:40 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/03 12:49:35 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

t_bool	open_write(t_fds *fds, t_string str, int flags)
{
	wati_close(fds->out);
	fds->out = -1;
	fds->out = open(str, flags, 0644);
	if (fds->out < 0)
		return (wati_error("permission denied: %s", str));
	free(str);
	return (TRUE);
}
