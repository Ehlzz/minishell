/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:14 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/05 20:35:30 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_fds fds);

t_bool	btree_cmd(t_btree **node, t_list **list, t_fds fds)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		free(cmd);
		return (FALSE);
	}
	cmd->oper = NO;
	if (!_btree_cmd(cmd, list, fds))
	{
		free(cmd);
		return (FALSE);
	}
	*node = btree_create_node(cmd);
	if (!*node)
	{
		free_cmd(cmd);
		return (wati_error("alloc fail"));
	}
	return (TRUE);
}

static t_bool	cmd_parse_token(t_list **new, t_list **list, t_fds *fds);

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_fds fds)
{
	t_list		*lst;
	t_list		*new;

	lst = NULL;
	while (*list && is_opercmd(get_token(*list)->oper))
	{
		if (!cmd_parse_token(&new, list, &fds))
		{
			wati_lstclear(&lst, free);
			return (FALSE);
		}
		if (new)
			wati_lstadd_back(&lst, new);
		(*list) = (*list)->next;
	}
	cmd->strs = lst;
	cmd->fds = fds;
	return (TRUE);
}

static t_bool	cmd_parse_redirect(t_list **list, t_fds *fds);

static t_bool	cmd_parse_token(t_list **new, t_list **list, t_fds *fds)
{
	t_token	*token;

	token = (*list)->content;
	*new = NULL;
	if (token->oper == NO)
	{
		*new = wati_lstnew(token->str);
		if (!*new)
			return (wati_error("alloc fail"));
		return (TRUE);
	}
	return (cmd_parse_redirect(list, fds));
}

static t_bool	cmd_parse_redirect(t_list **list, t_fds *fds)
{
	t_token	*token;
	t_token	*name;

	if (!(*list)->next || !(*list)->next->content)
		return (wati_error("no file given"));
	token = (*list)->content;
	free(token->str);
	(*list) = (*list)->next;
	name = (*list)->content;
	if (name->oper != NO)
		wati_error("syntax error near unexpected token '%s'", token->str);
	if (token->oper == R_IN)
		return (open_read(fds, name->str, O_RDONLY));
	if (token->oper == R_OUT)
		return (open_write(fds, name->str, O_WRONLY | O_CREAT | O_TRUNC));
	if (token->oper == H_OUT)
		return (open_write(fds, name->str, O_WRONLY | O_CREAT | O_APPEND));
	return (FALSE);
}

t_bool	is_opercmd(t_oper oper)
{
	return (oper == NO
		|| oper == H_IN
		|| oper == H_OUT
		|| oper == R_IN
		|| oper == R_OUT);
}
