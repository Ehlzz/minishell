/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/10 17:46:47 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

static t_list	*btree_build_cmd(t_btree **root, t_list *list, t_fds fds);
static t_list	*btree_build_oper(t_btree **root, t_list *list, t_fds fds);
static t_list	*btree_build_pipe(t_btree **root, t_list *list, t_fds fds);
static t_list	*btree_build_par(t_btree **root, t_list *list, t_fds fds);

t_list	*btree_build(t_btree **root, t_list *list)
{
	t_fds	fds;
	t_token	*token;

	if (!list)
		return (NULL);
	fds.in = 0;
	fds.out = 1;
	token = list->content;
	if (in_command(token))
		list = btree_build_cmd(root, list, fds);
	else if (token->oper == AND
		|| token->oper == OR)
		list = btree_build_oper(root, list, fds);
	else if (token->oper == PIPE)
		list = btree_build_pipe(root, list, fds);
	else if (token->oper == P_IN)
		list = btree_build_par(root, list, fds);
	else if (token->oper == P_OUT)
	{
		free(get_token(list)->str);
		return (list->next);
	}
	if (list)
		list = btree_build(root, list);
	return (list);
}

static t_list	*btree_build_cmd(t_btree **root, t_list *list, t_fds fds)
{
	t_btree	*node;
	t_cmd	*cmd;

	cmd = new_cmd(&list, fds);
	if (!cmd)
		return (NULL);
	node = btree_create_node(cmd);
	if (!node)
	{
		free_cmd(cmd);
		return (NULL);
	}
	add_cmd(root, node);
	return (list);
}

static t_list	*btree_build_oper(t_btree **root, t_list *list, t_fds fds)
{
	t_btree	*node;

	node = btree_node_oper(list->content, fds);
	if (!node)
	{
		wati_lstiter(list, free_token);
		return (NULL);
	}
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

static t_list	*btree_build_par(t_btree **root, t_list *list, t_fds fds)
{
	free(get_token(list)->str);
	if (*root == NULL)
		list = btree_build(root, list->next);
	else
		list = btree_build(&(*root)->right, list->next);
	return (list);
}
