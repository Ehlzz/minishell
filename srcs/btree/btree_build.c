/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 13:54:56 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

static t_bool	_btree_build(t_btree **root, t_list **list, t_shell *shell);

t_bool	btree_build(t_btree **root, t_list *list, t_shell *shell)
{
	if (!_btree_build(root, &list, shell))
	{
		btree_clear(*root, free_cmd);
		wati_lstiter(list, free_token);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	_btree_build(t_btree **root, t_list **list, t_shell *shell)
{
	if (!list)
		return (TRUE);
	if (!_btree_build_oper(root, list))
		return (FALSE);
	if (!_btree_build_pipe(root, list, shell))
		return (FALSE);
	if (*list)
	{
		if (get_token(*list)->oper == P_OUT)
			return (wati_error("parse error near '%s'", get_token(*list)->str));
		return (_btree_build(root, list, shell));
	}
	return (TRUE);
}
