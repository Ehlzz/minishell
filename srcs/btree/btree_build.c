/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/05 14:31:58 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

static t_bool	_btree_build(t_btree **root, t_list **list, t_fds fds);

t_bool	btree_build(t_btree **root, t_list *list)
{
	t_fds	fds;

	fds.in = 0;
	fds.out = 1;
	if (!_btree_build(root, &list, fds))
	{
		btree_clear(*root, free_cmd);
		wati_lstiter(list, free_token);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	_btree_build_oper(t_btree **root, t_list **list, t_fds fds);
static t_bool	_btree_build_pipe(t_btree **root, t_list **list, t_fds fds);

static t_bool	_btree_build(t_btree **root, t_list **list, t_fds fds)
{
	if (!list)
		return (TRUE);
	if (!_btree_build_oper(root, list, fds))
		return (FALSE);
	if (!_btree_build_pipe(root, list, fds))
		return (FALSE);
	if (*list)
		return (_btree_build(root, list, fds));
	return (TRUE);
}

static t_bool	_btree_build_oper(t_btree **root, t_list **list, t_fds fds)
{
	t_token	*token;

	if (!*list)
		return (TRUE);
	token = (*list)->content;
	if (token->oper == AND || token->oper == OR)
	{
		if (!btree_oper(root, list, fds))
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	_btree_build_pipe(t_btree **root, t_list **list, t_fds fds)
{
	t_token	*token;
	t_btree	*node;

	node = NULL;
	if (!*list)
		return (TRUE);
	token = (*list)->content;
	if (is_opercmd(token->oper))
	{
		if (!btree_cmd(&node, list, fds))
			return (FALSE);
	}
	if (*list)
		token = (*list)->content;
	if (token->oper == PIPE)
	{
		if (!btree_pipe(&node, list, fds))
			return (FALSE);
	}
	if (node)
		add_root(root, node);
	return (TRUE);
}
