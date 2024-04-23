/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build_par.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:20:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/20 14:20:23 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

static t_bool	_btree_build_par(t_btree **root, t_list **list, t_fds fds);

t_bool	btree_build_par(t_btree **root, t_list **list, t_fds fds)
{
	t_btree	**ptr;

	free(get_token(*list)->str);
	ptr = root;
	while (*ptr)
		ptr = &(*ptr)->right;
	*list = (*list)->next;
	return (_btree_build_par(ptr, list, fds));
}

static t_bool	_btree_build_par(t_btree **root, t_list **list, t_fds fds)
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
		free(get_token(*list)->str);
		*list = (*list)->next;
		return (TRUE);
	}
	if (*list)
		return (_btree_build_par(root, list, fds));
	wati_fprintf(STDERR_FILENO,
		"%s: Error: missing operator ')'\n", NAME);
	return (FALSE);
}
