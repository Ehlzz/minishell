/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_par.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:28:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/10 11:44:14 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

static t_bool	_btree_par(t_btree **root, t_list **list);

t_bool	btree_par(t_btree **root, t_list **list)
{
	t_token	*token;
	t_btree	*node;

	token = (*list)->content;
	if (token->oper != P_IN)
		return (wati_error("parsing"));
	free(token->str);
	*list = (*list)->next;
	if (!*list)
		return (wati_error("parse error near '('"));
	token = (*list)->content;
	if (token->oper == P_OUT)
		return (wati_error("empty parenthesis"));
	node = NULL;
	if (!_btree_par(&node, list))
		return (FALSE);
	if (get_token(*list)->oper == P_OUT)
		free(get_token(*list)->str);
	*root = node;
	get_cmd(node)->is_sub = TRUE;
	*list = (*list)->next;
	return (TRUE);
}

static t_bool	_btree_par(t_btree **root, t_list **list)
{
	if (!_btree_build_oper(root, list))
		return (FALSE);
	if (!_btree_build_pipe(root, list))
		return (FALSE);
	if (*list && get_token(*list)->oper != P_OUT)
		return (_btree_par(root, list));
	if (!*list)
		return (wati_error("parenthesis not close"));
	return (TRUE);
}
