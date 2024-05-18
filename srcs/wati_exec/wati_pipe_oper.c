/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:31 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 14:11:53 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

t_bool	_wati_pipe_oper(t_btree *node, t_pipe *fd,
				t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_pipe	pipe;

	pid = fork();
	if (!pid)
	{
		wati_lstclear(pids, free);
		wati_close(fd->pipe[0]);
		wati_close(fd->pipe[1]);
		pipe = reset_pipe();
		pipe.in = fd->in;
		_wati_exec(node, pipe, shell);
		wati_close(fd->in);
		wati_lstclear(&shell->env, free);
		btree_clear(shell->root, free_cmd);
		exit(g_err);
	}
	add_pid(pids, pid);
	return (TRUE);
}
