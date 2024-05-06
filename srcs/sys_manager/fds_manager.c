/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/02 15:21:05 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

static t_bool	_wati_dup2(t_fd fd, t_fd std);

t_bool	wati_dup2(t_fds fds, t_pipe *fd)
{
	if (fd->in != 0 && fd->in >= 0)
	{
		wati_fprintf(2, "pipe_in\n");
		if (!_wati_dup2(fd->in, STDIN_FILENO))
			return (FALSE);
	}
	if (fd->pipe[1] != 1 && fd->pipe[1] >= 0)
	{
		wati_fprintf(2, "pipe_out\n");
		if (!_wati_dup2(fd->pipe[1], STDOUT_FILENO))
			return (FALSE);
	}
	if (fds.in != 0 && fds.in >= 0)
	{
		wati_fprintf(2, "fd_in\n");
		if (!_wati_dup2(fds.in, STDIN_FILENO))
			return (FALSE);
	}
	if (fds.out != 1 && fds.out >= 0)
	{
		wati_fprintf(2, "fd_out\n");
		if (!_wati_dup2(fds.out, STDOUT_FILENO))
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	_wati_dup2(t_fd fd, t_fd std)
{
	if (dup2(fd, std) < 0
		&& dup2(fd, std) < 0
		&& dup2(fd, std) < 0)
		return (FALSE);
	return (TRUE);
}

t_pipe	reset_pipe(void)
{
	t_pipe	fd;

	fd.in = -1;
	fd.pipe[0] = -1;
	fd.pipe[1] = -1;
	return (fd);
}
