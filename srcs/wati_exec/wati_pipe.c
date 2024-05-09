/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:59:30 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/09 15:42:37 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static t_bool	_wati_pipe(t_btree *node, t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

t_bool	wati_pipe(t_btree *node, t_list **pids, t_shell *shell)
{
	t_pipe	*fd;

	fd = &shell->fd;
	fd->in = -1;
	_wati_pipe_o(node->left, fd, pids, shell);
	_wati_pipe_l(node->right, fd, pids, shell);
	return (wait_pids(shell->pids));
}

static t_bool	_wati_pipe(t_btree *node, t_list **pids, t_shell *shell)
{
	t_pipe	*fd;

	fd = &shell->fd;
	*fd = reset_pipe();
	_wati_pipe_o(node->left, fd, pids, shell);
	_wati_pipe_o(node->right, fd, pids, shell);
	return (TRUE);
}

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = node->item;
	if (cmd->oper == PIPE)
		return (_wati_pipe(node, pids, shell));
	pipe(fd->pipe);
	if (cmd->oper == NO)
		pid = wati_execve(cmd, fd, pids, shell);
	swap_spipe(fd);
	return (TRUE);
}

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = node->item;
	if (cmd->oper == PIPE)
		return (_wati_pipe(node, pids, shell));
	if (cmd->oper == NO)
		pid = wati_execve(cmd, fd, pids, shell);
	wati_close(fd->pipe[0]);
	return (TRUE);
}
