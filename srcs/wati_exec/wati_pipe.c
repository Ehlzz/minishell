/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:59:30 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/30 20:24:14 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static t_bool	_wati_pipe(t_btree *node, t_shell *shell);

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

t_bool	wati_pipe(t_btree *node, t_shell *shell)
{
	t_list	*pids;
	t_pipe	*fd;

	fd = &shell->fd;
	pids = NULL;
	fd->in = -1;
	_wati_pipe_o(node->left, fd, &pids, shell);
	_wati_pipe_l(node->right, fd, &pids, shell);
	wait_pids(pids);
	return (TRUE);
}

static t_bool	_wati_pipe(t_btree *node, t_shell *shell)
{
	t_list	*pids;
	t_pipe	*fd;

	fd = &shell->fd;
	pids = NULL;
	fd->in = -1;
	_wati_pipe_o(node->left, fd, &pids, shell);
	_wati_pipe_o(node->right, fd, &pids, shell);
	wait_pids(pids);
	return (TRUE);
}

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = node->item;
	if (cmd->oper == PIPE)
		_wati_pipe(node, shell);
	pipe(fd->pipe);
	wati_fprintf(2, "pipe: %i->%i\n", fd->pipe[1], fd->pipe[0]);
	link_cmd(&cmd->fds, fd->in, fd->pipe[1]);
	if (cmd->oper == NO)
	{
		pid = wati_execve(cmd, shell);
		add_pid(pids, pid);
	}
	close(fd->pipe[1]);
	fd->in = fd->pipe[0];
	return (TRUE);
}

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = node->item;
	if (cmd->oper == PIPE)
		_wati_pipe(node, shell);
	link_cmd(&cmd->fds, fd->in, -1);
	if (cmd->oper == NO)
	{
		pid = wati_execve(cmd, shell);
		add_pid(pids, pid);
	}
	return (TRUE);
}
