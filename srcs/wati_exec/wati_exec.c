/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/10 16:42:18 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

static t_bool	_wati_and(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell);
static t_bool	_wati_or(t_btree *node,
					t_pipe *fd, t_list **pids, t_shell *shell);

t_bool	wati_exec(t_shell shell)
{
	if (!shell.root)
		return (FALSE);
	return (_wati_exec(shell.root, &shell.fd, &shell.pids, &shell));
}

t_bool	_wati_exec(t_btree *node, t_pipe *fd, t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	t_list	*lst;

	cmd = node->item;
	lst = NULL;
	*pids = NULL;
	shell->fd = reset_pipe();
	if (cmd->oper == AND)
		return (_wati_and(node, fd, pids, shell));
	else if (cmd->oper == OR)
		return (_wati_or(node, fd, pids, shell));
	else if (cmd->oper == PIPE)
		return (wati_pipe(node, fd, pids, shell));
	else if (cmd->oper == NO)
	{
		wati_execve(cmd, fd, &lst, shell);
		if (wait_pids(lst))
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	_wati_and(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	if (_wati_exec(node->left, fd, pids, shell))
		return (_wati_exec(node->right, fd, pids, shell));
	else
		return (FALSE);
}

static t_bool	_wati_or(t_btree *node, t_pipe *fd,
					t_list **pids, t_shell *shell)
{
	if (!_wati_exec(node->left, fd, pids, shell))
		return (_wati_exec(node->right, fd, pids, shell));
	else
		return (TRUE);
}
