/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 12:53:39 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <fcntl.h>

static t_bool	wati_dup2(t_fd fd, t_fd std);
static t_bool	open_file(t_file *file, t_fds *fds, t_list *env);

t_bool	wati_dup_fds(t_fds fds)
{
	t_bool	r;

	r = TRUE;
	if (fds.in > 2)
	{
		if (!wati_dup2(fds.in, STDIN_FILENO))
			r = FALSE;
		close(fds.in);
	}
	if (fds.out > 2)
	{
		if (r && !wati_dup2(fds.out, STDOUT_FILENO))
			r = FALSE;
		close(fds.in);
	}
	return (r);
}

t_bool	wati_dup_files(t_fds *fds, t_list *files, t_pipe *fd, t_list *env)
{
	wati_close(fd->pipe[0]);
	fds->in = 0;
	fds->out = 1;
	if (fd->in > 2)
		fds->in = fd->in;
	if (fd->pipe[1] > 2)
		fds->out = fd->pipe[1];
	while (files)
	{
		if (!open_file(files->content, fds, env))
		{
			wati_close(fds->in);
			wati_close(fds->out);
			return (FALSE);
		}
		files = files->next;
	}
	//wati_fprintf(2, "%i %i\n", fds->in, fds->out);
	return (TRUE);
}

static t_bool	open_file(t_file *file, t_fds *fds, t_list *env)
{
	file->name = verify_token(file->name, env);
	if (file->oper == R_IN)
	{
		wati_close(fds->in);
		fds->in = open_read(file->name, O_RDONLY);
	}
	else if (file->oper == H_IN)
	{
		wati_close(fds->in);
		fds->in = file->fd;
		file->fd = -1;
	}
	else if (file->oper == R_OUT)
	{
		wati_close(fds->out);
		fds->out = open_write(file->name, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (file->oper == H_OUT)
	{
		wati_close(fds->out);
		fds->out = open_write(file->name, O_WRONLY | O_CREAT | O_APPEND);
	}
	if (fds->in < 0 | fds->out < 0)
		return (FALSE);
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
