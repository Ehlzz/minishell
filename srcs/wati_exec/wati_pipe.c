/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:59:30 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/10 16:42:50 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static t_bool	_wati_pipe(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

t_bool	wati_pipe(t_btree *node, t_pipe *fd, t_list **pids, t_shell *shell)
{
	*fd = reset_pipe();
	fd->in = -1;
	_wati_pipe_o(node->left, fd, pids, shell);
	_wati_pipe_l(node->right, fd, pids, shell);
	return (wait_pids(shell->pids));
}

static t_bool	_wati_pipe(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	_wati_pipe_o(node->left, fd, pids, shell);
	_wati_pipe_o(node->right, fd, pids, shell);
	return (TRUE);
}

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = node->item;
	if (cmd->oper == PIPE)
		return (_wati_pipe(node, fd, pids, shell));
	if (cmd->oper == AND || cmd->oper == OR)
		_wati_pipe_oper(node, fd, pids, shell);
	pipe(fd->pipe);
	if (cmd->oper == NO)
		wati_execve(cmd, fd, pids, shell);
	swap_spipe(fd);
	return (TRUE);
}

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = node->item;
	if (cmd->oper == PIPE)
		return (_wati_pipe(node, fd, pids, shell));
	if (cmd->oper == AND || cmd->oper == OR)
		_wati_pipe_oper(node, fd, pids, shell);
	if (cmd->oper == NO)
		wati_execve(cmd, fd, pids, shell);
	wati_close(fd->pipe[0]);
	return (TRUE);
}
