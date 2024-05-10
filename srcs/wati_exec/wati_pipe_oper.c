/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:31 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/10 16:44:06 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

t_bool	_wati_pipe_oper(t_btree *node, t_pipe *fd,
				t_list **pids, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		exit(_wati_exec(node, fd, pids, shell));
	}
	add_pid(pids, pid);
	return (TRUE);
}
