/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/05 14:46:20 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

static t_list	*btree_build_cmd(t_btree **root, t_list *list, t_fds fds);
static t_list	*btree_build_oper(t_btree **root, t_list *list, t_fds fds);
static t_list	*btree_build_pipe(t_btree **root, t_list *list, t_fds fds);

t_list	*btree_build(t_btree **root, t_list *list)
{
	t_fds	fds;

	if (!list)
		return (NULL);
	fds.in = 0;
	fds.out = 1;
	if (get_token(list)->oper == NO)
		list = btree_build_cmd(root, list, fds);
	else if (get_token(list)->oper == AND
		|| get_token(list)->oper == OR)
		list = btree_build_oper(root, list, fds);
	else if (get_token(list)->oper == PIPE)
		list = btree_build_pipe(root, list, fds);
	if (list)
		btree_build(root, list);
	return (list);
}

static t_list	*btree_build_cmd(t_btree **root, t_list *list, t_fds fds)
{
	t_btree	*node;
	t_cmd	*cmd;

	cmd = new_cmd(&list, fds);
	node = btree_create_node(cmd);
	add_cmd(root, node);
	return (list);
}

static t_list	*btree_build_oper(t_btree **root, t_list *list, t_fds fds)
{
	t_btree	*node;

	node = btree_node_oper(list->content, fds);
	new_root(root, node);
	return (list->next);
}

static t_list	*btree_build_pipe(t_btree **root, t_list *list, t_fds fds)
{
	if ((get_cmd(*root)->oper == AND
			|| get_cmd(*root)->oper == OR))
		list = btree_build_oper(&(*root)->right, list, fds);
	else
		list = btree_build_oper(root, list, fds);
	return (list);
}
