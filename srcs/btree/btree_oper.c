/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:07 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:29:17 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"

t_bool	btree_oper(t_btree **root, t_list **list)
{
	t_token	*token;
	t_btree	*new;
	t_cmd	*cmd;

	if (!(*list)->next)
		return (wati_error("parse error near '%s'", get_token(*list)->str));
	token = (*list)->content;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (wati_error("alloc fail"));
	free(token->str);
	cmd->oper = token->oper;
	cmd->strs = NULL;
	cmd->files = files_build(NULL, -1, NULL, NULL);
	new = btree_create_node(cmd);
	if (!new)
	{
		free(cmd);
		return (wati_error("alloc fail"));
	}
	new_root(root, new);
	(*root)->right = NULL;
	(*list) = (*list)->next;
	return (TRUE);
}
