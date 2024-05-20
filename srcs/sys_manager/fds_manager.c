/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:27:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 19:11:51 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <fcntl.h>

static t_bool	wati_dup2(t_fd fd, t_fd std);
static t_bool	open_file(t_file *file, t_fds *fds, t_list *env);

void	__wati_dup_files(t_fds fds)
{
	if (fds.in > 2)
	{
		wati_dup2(fds.in, STDIN_FILENO);
		close(fds.in);
	}
	if (fds.out > 2)
	{
		wati_dup2(fds.out, STDOUT_FILENO);
		close(fds.out);
	}
}

t_bool	wati_dup_files(t_list *files, t_pipe *fd, t_list *env)
{
	t_fds	fds;

	wati_close(fd->pipe[0]);
	fds.in = 0;
	fds.out = 1;
	if (fd->in > 2)
		fds.in = fd->in;
	if (fd->pipe[1] > 2)
		fds.out = fd->pipe[1];
	while (files)
	{
		if (!open_file(files->content, &fds, env))
		{
			wati_close(fds.in);
			wati_close(fds.out);
			return (FALSE);
		}
		files = files->next;
	}
	__wati_dup_files(fds);
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
