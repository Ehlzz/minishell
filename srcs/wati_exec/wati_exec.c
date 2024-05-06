/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/02 16:11:01 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

static t_bool	_wati_exec(t_btree *node, t_shell *shell);

static t_bool	_wati_and(t_btree *node, t_shell *shell);
static t_bool	_wati_or(t_btree *node, t_shell *shell);

t_bool	wati_exec(t_shell shell)
{
	if (!shell.root)
		return (FALSE);
	return (_wati_exec(shell.root, &shell));
}

static t_bool	_wati_exec(t_btree *node, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		r;

	cmd = node->item;
	if (cmd->oper == AND)
		return (_wati_and(node, shell));
	if (cmd->oper == OR)
		return (_wati_or(node, shell));
	if (cmd->oper == PIPE)
		return (wati_pipe(node, shell));
	else if (cmd->oper == NO)
	{
		shell->fd = reset_pipe();
		pid = wati_execve(cmd, &shell->fd, shell);
		waitpid(pid, &r, 0);
		if (r)
			return (FALSE);
		else
			return (TRUE);
	}
	return (TRUE);
}

static t_bool	_wati_and(t_btree *node, t_shell *shell)
{
	if (_wati_exec(node->left, shell))
		return (_wati_exec(node->right, shell));
	else
		return (FALSE);
}

static t_bool	_wati_or(t_btree *node, t_shell *shell)
{
	if (!_wati_exec(node->left, shell))
		return (_wati_exec(node->right, shell));
	else
		return (TRUE);
}
