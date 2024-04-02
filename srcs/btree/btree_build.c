/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/01 14:23:09 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

t_btree	*btree_node_oper(t_token *token, t_fds fds);

t_list	*btree_build(t_btree **root, t_list *list)
{
	t_btree	**ptr;
	t_btree	*node;
	t_cmd	*cmd;
	t_fds	fds;

	if (!list)
		return (NULL);
	fds.in = 0;
	fds.out = 1;
	printf("ICI\n");
	if (get_token(list)->oper == NO)
	{
		cmd = new_cmd(&list, fds);
		node = btree_create_node(cmd);
		ptr = root;
		while (*ptr != NULL)
			*ptr = (*ptr)->right;
		*ptr = node;
	}
	else if (get_token(list)->oper == PIPE)
	{
		node = btree_node_oper(list->content, fds);
		node->left = *root;
		*root = node;
		list = list->next;
	}
	if (list)
		btree_build(root, list);
	return (list);
}

t_btree	*btree_node_oper(t_token *token, t_fds fds)
{
	t_btree	*node;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->fds = fds;
	cmd->strs = NULL;
	cmd->oper = token->oper;
	node = btree_create_node(cmd);
	return (node);
}
