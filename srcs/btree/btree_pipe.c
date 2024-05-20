/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:49:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 20:11:11 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_btree_pipe(t_btree **root, t_btree *node);

t_bool	_btree_build_pipe(t_btree **root, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_btree	*node;

	node = NULL;
	shell->node = &node;
	if (!*list)
		return (TRUE);
	token = (*list)->content;
	if (is_opercmd(token->oper))
	{
		if (!btree_cmd(&node, list, shell))
			return (FALSE);
	}
	if (*list)
		token = (*list)->content;
	if (token->oper == PIPE)
	{
		if (!btree_pipe(&node, list, shell))
			return (FALSE);
	}
	if (node)
		add_root(root, node);
	return (TRUE);
}

t_bool	btree_pipe(t_btree **root, t_list **list, t_shell *shell)
{
	t_btree	*node;

	node = NULL;
	if (!*root)
		return (wati_error(2, "parse error near '%s'", get_token(*list)->str));
	while (*list && get_token(*list)->oper == PIPE)
	{
		if (!(*list)->next || !is_opercmd(get_token((*list)->next)->oper))
		{
			if (*root)
				btree_clear(*root, free_cmd);
			return (wati_error(2,
					"parse error near '%s'", get_token(*list)->str));
		}
		free(get_token(*list)->str);
		(*list) = (*list)->next;
		if (!btree_cmd(&node, list, shell))
			return (FALSE);
		if (!_btree_pipe(root, node))
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	_btree_pipe(t_btree **root, t_btree *node)
{
	t_btree	*new;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (wati_error(3, "alloc fail"));
	cmd->oper = PIPE;
	cmd->strs = NULL;
	cmd->files = NULL;
	new = btree_create_node(cmd);
	if (!new)
	{
		free(cmd);
		return (wati_error(3, "alloc fail"));
	}
	new_root(root, new);
	(*root)->right = node;
	return (TRUE);
}
