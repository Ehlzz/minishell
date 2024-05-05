/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/01 13:28:36 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

void	swap_spipe(t_pipe *fd)
{
	wati_close(fd->in);
	wati_close(fd->pipe[1]);
	fd->in = fd->pipe[0];
	fd->pipe[1] = -1;
}
