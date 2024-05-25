/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:49:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/25 17:07:00 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_btree_pipe(t_btree **root, t_btree *node);

t_bool	_btree_build_pipe(t_btree **root, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_btree	*node;

	if (!*list)
		return (TRUE);
	token = (*list)->content;
	if (*root && ((*root)->right || is_opercmd(get_cmd(*root)->oper)))
		return (wati_error(2,
				"parse error near '%s'", token->str));
	node = NULL;
	if (is_opercmd(token->oper) && !btree_cmd(&node, list, shell))
		return (FALSE);
	if (*list)
		token = (*list)->content;
	if (token->oper == PIPE && !btree_pipe(&node, list, shell))
	{
		btree_clear(&node, free_cmd);
		return (FALSE);
	}
	if (node)
		add_root(root, node);
	return (TRUE);
}

t_bool	btree_pipe(t_btree **root, t_list **list, t_shell *shell)
{
	t_btree	*node;

	if (!*root)
		return (wati_error(2, "parse error near '%s'", get_token(*list)->str));
	while (*list && get_token(*list)->oper == PIPE)
	{
		if (!(*list)->next || !is_opercmd(get_token((*list)->next)->oper))
		{
			return (wati_error(2,
					"parse error near '%s'", get_token(*list)->str));
		}
		free(get_token(*list)->str);
		(*list) = (*list)->next;
		node = NULL;
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
	{
		btree_clear(&node, free_cmd);
		return (wati_error(3, "alloc fail"));
	}
	cmd->oper = PIPE;
	cmd->strs = NULL;
	cmd->files = NULL;
	new = btree_create_node(cmd);
	if (!new)
	{
		free(cmd);
		btree_clear(&node, free_cmd);
		return (wati_error(3, "alloc fail"));
	}
	new_root(root, new);
	(*root)->right = node;
	return (TRUE);
}
