/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:07 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/20 14:29:12 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"

// TRUC A REVOIR
t_btree	*btree_node_oper(t_token *token, t_fds fds)
{
	t_btree	*node;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		wati_fprintf(STDERR_FILENO, "%s: Error: alloc fail\n", NAME);
		return (NULL);
	}
	cmd->fds = fds;
	cmd->strs = NULL;
	cmd->oper = token->oper;
	node = btree_create_node(cmd);
	if (!node)
	{
		wati_fprintf(STDERR_FILENO, "%s: Error: alloc fail\n", NAME);
		free(cmd);
		return (NULL);
	}
	return (node);
}
