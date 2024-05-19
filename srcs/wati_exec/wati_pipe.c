/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:59:30 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 13:24:07 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static t_bool	wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);
static t_bool	wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);

t_bool	wati_pipe(t_btree *node, t_pipe fd, t_shell *shell)
{
	t_list	*pids;
	t_cmd	*cmd;

	pids = NULL;
	cmd = node->item;
	if (cmd->oper == NO)
	{
		wati_execve(cmd, &fd, &pids, shell);
		close_spipe(fd);
		return (wait_pids(pids));
	}
	else if (cmd->oper == PIPE)
	{
		wati_pipe_o(node->left, &fd, &pids, shell);
		wati_pipe_l(node->right, &fd, &pids, shell);
		return (wait_pids(pids));
	}
	else
		return (FALSE);
	return (TRUE);
}

static t_bool	wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	if (get_cmd(node)->oper == PIPE)
	{
		wati_pipe_o(node->left, fd, pids, shell);
		wati_pipe_o(node->right, fd, pids, shell);
	}
	else
		return (_wati_pipe_o(node, fd, pids, shell));
	return (TRUE);
}

static t_bool	wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	if (get_cmd(node)->oper == PIPE)
	{
		wati_pipe_o(node->left, fd, pids, shell);
		wati_pipe_l(node->right, fd, pids, shell);
	}
	else
	{
		return (_wati_pipe_l(node, fd, pids, shell));
	}
	return (TRUE);
}

static t_bool	_wati_pipe_o(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = node->item;
	if (cmd->oper == AND || cmd->oper == OR)
		_wati_pipe_oper(node, fd, pids, shell);
	pipe(fd->pipe);
	if (cmd->oper == NO)
		wati_execve_pipe(cmd, fd, pids, shell);
	swap_spipe(fd);
	return (TRUE);
}

static t_bool	_wati_pipe_l(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = node->item;
	if (cmd->oper == AND || cmd->oper == OR)
		_wati_pipe_oper(node, fd, pids, shell);
	if (cmd->oper == NO)
		wati_execve_pipe(cmd, fd, pids, shell);
	wati_close(fd->in);
	return (TRUE);
}
