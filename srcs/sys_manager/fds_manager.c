/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/30 20:24:36 by bedarenn         ###   ########.fr       */
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

t_bool	wati_dup2(t_fds fds)
{
	if (fds.in != 0 && fds.in >= 0)
	{
		if (dup2(fds.in, STDIN_FILENO) < 0
			&& dup2(fds.in, STDIN_FILENO) < 0
			&& dup2(fds.in, STDIN_FILENO) < 0)
			return (FALSE);
	}
	if (fds.out != 1 && fds.out >= 0)
	{
		if (dup2(fds.out, STDOUT_FILENO) < 0
			&& dup2(fds.out, STDOUT_FILENO) < 0
			&& dup2(fds.out, STDOUT_FILENO) < 0)
			return (FALSE);
	}
	return (TRUE);
}

void	link_cmd(t_fds *cmd_fds, t_fd in, t_fd out)
{

	if (cmd_fds->in == 0 && in > 2)
		cmd_fds->in = in;
	if (cmd_fds->out == 1 && out > 2)
		cmd_fds->out = out;
}
