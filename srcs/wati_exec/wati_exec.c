/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/09 17:04:32 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

static t_bool	_wati_exec(t_btree *node, t_list **pids, t_shell *shell);

static t_bool	_wati_and(t_btree *node, t_list **pids, t_shell *shell);
static t_bool	_wati_or(t_btree *node, t_list **pids, t_shell *shell);

t_bool	wati_exec(t_shell shell)
{
	if (!shell.root)
		return (FALSE);
	return (_wati_exec(shell.root, &shell.pids, &shell));
}

static t_bool	_wati_exec(t_btree *node, t_list **pids, t_shell *shell)
{
	t_cmd	*cmd;
	t_list	*lst;

	cmd = node->item;
	lst = NULL;
	*pids = NULL;
	shell->fd = reset_pipe();
	if (cmd->oper == AND)
		return (_wati_and(node, pids, shell));
	else if (cmd->oper == OR)
		return (_wati_or(node, pids, shell));
	else if (cmd->oper == PIPE)
		return (wati_pipe(node, pids, shell));
	else if (cmd->oper == NO)
	{
		wati_execve(cmd, &shell->fd, &lst, shell);
		if (wait_pids(lst))
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	_wati_and(t_btree *node, t_list **pids, t_shell *shell)
{
	if (_wati_exec(node->left, pids, shell))
		return (_wati_exec(node->right, pids, shell));
	else
		return (FALSE);
}

static t_bool	_wati_or(t_btree *node, t_list **pids, t_shell *shell)
{
	if (!_wati_exec(node->left, pids, shell))
		return (_wati_exec(node->right, pids, shell));
	else
		return (TRUE);
}
