/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_par.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:28:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 13:26:55 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

static t_bool	_btree_par(t_btree **root, t_list **list, t_shell *shell);

t_bool	btree_par(t_btree **root, t_list **list, t_shell *shell)
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
	if (!_btree_par(&node, list, shell))
	{
		if (node)
			btree_clear(node, free_cmd);
		return (FALSE);
	}
	if (get_token(*list)->oper == P_OUT)
		free(get_token(*list)->str);
	*root = node;
	*list = (*list)->next;
	return (TRUE);
}

static t_bool	_btree_par(t_btree **root, t_list **list, t_shell *shell)
{
	if (!_btree_build_oper(root, list))
		return (FALSE);
	if (!_btree_build_pipe(root, list, shell))
		return (FALSE);
	if (*list && get_token(*list)->oper != P_OUT)
		return (_btree_par(root, list, shell));
	if (!*list)
		return (wati_error("parenthesis not close"));
	return (TRUE);
}
