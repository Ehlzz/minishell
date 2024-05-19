/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:14 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 17:39:10 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_shell *shell);

t_bool	btree_cmd(t_btree **node, t_list **list, t_shell *shell)
{
	t_cmd	*cmd;

	if (get_token(*list)->oper == P_IN)
		return (btree_par(node, list, shell));
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		free(cmd);
		return (FALSE);
	}
	cmd->oper = NO;
	cmd->files = NULL;
	if (!_btree_cmd(cmd, list, shell))
	{
		free(cmd);
		return (FALSE);
	}
	*node = btree_create_node(cmd);
	if (!*node)
	{
		free_cmd(cmd);
		return (wati_error(3, "alloc fail"));
	}
	return (TRUE);
}

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_list **new,
					t_shell *shell);

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_list		*new;

	cmd->strs = NULL;
	while (*list && is_opercmd(get_token(*list)->oper))
	{
		if (!cmd_parse_token(cmd, list, &new, shell))
		{
			wati_lstclear(&cmd->strs, free);
			return (FALSE);
		}
		if (new)
			wati_lstadd_back(&cmd->strs, new);
	}
	return (TRUE);
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell);

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_list **new,
					t_shell *shell)
{
	t_token	*token;

	token = (*list)->content;
	*new = NULL;
	if (!is_opercmd(token->oper) || token->oper == P_IN)
		return (wati_error(2, "parse error near '%s'", get_token(*list)->str));
	if (token->oper == NO)
	{
		*new = wati_lstnew(token->str);
		if (!*new)
			return (wati_error(3, "alloc fail"));
		(*list) = (*list)->next;
		return (TRUE);
	}
	return (cmd_parse_redirect(cmd, list, shell));
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_token	*name;

	if (!(*list)->next || !(*list)->next->content)
		return (wati_error(2, "no file given"));
	token = (*list)->content;
	(*list) = (*list)->next;
	name = (*list)->content;
	(*list) = (*list)->next;
	if (name->oper != NO)
		wati_error(2, "syntax error near unexpected token '%s'", name->str);
	free(token->str);
	if (token->oper == R_IN)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == R_OUT)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == H_IN)
		return (add_fd(&cmd->files, token->oper,
				here_doc(name->str, cmd, list, shell)));
	else if (token->oper == H_OUT)
		return (add_file(&cmd->files, token->oper, name->str));
	return (FALSE);
}

t_bool	is_opercmd(t_oper oper)
{
	return (oper == NO
		|| oper == H_IN
		|| oper == H_OUT
		|| oper == R_IN
		|| oper == R_OUT
		|| oper == P_IN);
}
