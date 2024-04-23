/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/20 14:16:22 by bedarenn         ###   ########.fr       */
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
		wati_lstiter(list, free_token);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	_btree_build(t_btree **root, t_list **list, t_fds fds)
{
	t_token	*token;

	if (!list)
		return (TRUE);
	token = (*list)->content;
	if (in_command(token))
	{
		if (!btree_build_cmd(root, list, fds))
			return (FALSE);
	}
	else if (token->oper == AND || token->oper == OR)
	{
		if (!btree_build_oper(root, list, fds))
			return (FALSE);
	}
	else if (token->oper == PIPE)
	{
		if (!btree_build_pipe(root, list, fds))
			return (FALSE);
	}
	else if (token->oper == P_IN)
	{
		if (!btree_build_par(root, list, fds))
			return (FALSE);
	}
	else if (token->oper == P_OUT)
	{
		wati_fprintf(STDERR_FILENO,
			"%s: Error: operator '%s'\n", NAME, token->str);
		return (FALSE);
	}
	if (*list)
	{
		if (!_btree_build(root, list, fds))
			return (FALSE);
	}
	return (TRUE);
}
