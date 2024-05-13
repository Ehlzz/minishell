/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:31 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/13 15:16:41 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

t_bool	_wati_pipe_oper(t_btree *node, t_pipe *fd,
				t_list **pids, t_shell *shell)
{
	t_bool	r;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		wati_lstclear(pids, free);
		close_spipe(*fd);
		r = _wati_exec(node, fd, shell);
		wati_lstclear(&shell->env, free);
		btree_clear(shell->root, free_cmd);
		exit(r);
	}
	add_pid(pids, pid);
	return (TRUE);
}
