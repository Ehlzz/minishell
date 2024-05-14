/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn < bedarenn@student.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/14 12:51:43 by bedarenn         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

#include <sys/wait.h>

static t_bool	_wati_and(t_btree *node, t_pipe fd, t_shell *shell);
static t_bool	_wati_or(t_btree *node, t_pipe fd, t_shell *shell);

t_bool	wati_exec(t_shell shell)
{
	t_pipe	fd;

	if (!shell.root)
		return (FALSE);
	fd = reset_pipe();
	return (_wati_exec(shell.root, fd, &shell));
}

t_bool	_wati_exec(t_btree *node, t_pipe fd, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = node->item;
	if (cmd->oper == AND)
		return (_wati_and(node, fd, shell));
	else if (cmd->oper == OR)
		return (_wati_or(node, fd, shell));
	else
		return (wati_pipe(node, fd, shell));
	return (TRUE);
}

static t_bool	_wati_and(t_btree *node, t_pipe fd, t_shell *shell)
{
	if (_wati_exec(node->left, fd, shell))
		return (_wati_exec(node->right, fd, shell));
	else
		return (FALSE);
}

static t_bool	_wati_or(t_btree *node, t_pipe fd, t_shell *shell)
{
	if (!_wati_exec(node->left, fd, shell))
		return (_wati_exec(node->right, fd, shell));
	else
		return (TRUE);
}
