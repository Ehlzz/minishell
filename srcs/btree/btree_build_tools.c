/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:52:59 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 12:55:29 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

t_bool	btree_build_cmd(t_btree **root, t_list **list, t_fds fds)
{
	t_btree	*node;
	t_cmd	*cmd;

	cmd = new_cmd(list, fds);
	if (!cmd)
		return (FALSE);
	node = btree_create_node(cmd);
	if (!node)
	{
		free_cmd(cmd);
		return (wati_error("alloc fail"));
	}
	add_cmd(root, node);
	return (TRUE);
}

t_bool	btree_build_oper(t_btree **root, t_list **list, t_fds fds)
{
	t_btree	*node;

	if (*root == NULL
		|| ((get_cmd(*root)->oper == PIPE
				|| get_cmd(*root)->oper == AND
				||get_cmd(*root)->oper == OR)
			&& (*root)->right == NULL))
		return (wati_error("operator '%s'", get_token(*list)->str));
	node = btree_node_oper((*list)->content, fds);
	if (!node)
		return (FALSE);
	free(get_token(*list)->str);
	new_root(root, node);
	*list = (*list)->next;
	return (TRUE);
}

t_bool	btree_build_pipe(t_btree **root, t_list **list, t_fds fds)
{
	if (*root == NULL)
		return (wati_error("operator '%s'", get_token(*list)->str));
	if ((get_cmd(*root)->oper == AND || get_cmd(*root)->oper == OR))
		return (btree_build_oper(&(*root)->right, list, fds));
	return (btree_build_oper(root, list, fds));
}
