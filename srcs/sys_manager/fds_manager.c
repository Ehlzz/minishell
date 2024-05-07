/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:48:25 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <fcntl.h>

static t_bool	wati_dup2(t_fd fd, t_fd std);

t_bool	wati_dup_files(t_files files, t_pipe *fd)
{
	t_fds	fds;

	if (files.r_in)
		fds.in = open_read(files.r_in, O_RDONLY);
	else if (files.h_in > 2)
		fds.in = files.h_in;
	else if (fd->in > 2)
		fds.in = fd->in;
	else
		fds.in = STDIN_FILENO;
	if (files.r_out)
		fds.out = open_write(files.r_out, O_WRONLY | O_CREAT | O_TRUNC);
	else if (files.h_out)
		fds.out = open_write(files.h_out, O_WRONLY | O_CREAT | O_APPEND);
	else if (fd->pipe[1] > 2)
		fds.out = fd->pipe[1];
	else
		fds.out = STDOUT_FILENO;
	if (fds.in > 2)
		wati_dup2(fds.in, STDIN_FILENO);
	if (fds.out > 2)
		wati_dup2(fds.out, STDOUT_FILENO);
	return (TRUE);
}

static t_bool	wati_dup2(t_fd fd, t_fd std)
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
