/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:49:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/05 14:30:40 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	_btree_pipe(t_btree **root, t_btree *node, t_fds fds);

t_bool	btree_pipe(t_btree **root, t_list **list, t_fds fds)
{
	t_btree	*node;

	if (!*root)
		return (wati_error("parse error near '%s'", get_token(*list)->str));
	while (*list && get_token(*list)->oper == PIPE)
	{
		if (!(*list)->next || !is_opercmd(get_token((*list)->next)->oper))
			return (wati_error("parse error near '%s'", get_token(*list)->str));
		free(get_token(*list)->str);
		(*list) = (*list)->next;
		if (!btree_cmd(&node, list, fds))
			return (FALSE);
		if (!_btree_pipe(root, node, fds))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	_btree_pipe(t_btree **root, t_btree *node, t_fds fds)
{
	t_btree	*new;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (wati_error("alloc fail"));
	cmd->oper = PIPE;
	cmd->strs = NULL;
	cmd->fds = fds;
	new = btree_create_node(cmd);
	if (!new)
	{
		free(cmd);
		return (wati_error("alloc fail"));
	}
	new_root(root, new);
	(*root)->right = node;
	return (TRUE);
}
