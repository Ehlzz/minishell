/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:14:23 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/01 13:18:36 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

void	wati_close(t_fd fd)
{
	if (fd > 2)
		close(fd);
}

void	close_fds(t_fds fds)
{
	wati_close(fds.in);
	wati_close(fds.out);
}

void	close_pipe(int pipe[2])
{
	wati_close(pipe[0]);
	wati_close(pipe[1]);
}

void	close_spipe(t_pipe fd)
{
	wati_close(fd.in);
	close_pipe(fd.pipe);
}
