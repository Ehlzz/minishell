/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:14 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/25 16:34:15 by bedarenn         ###   ########.fr       */
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
		return (FALSE);
	cmd->oper = NO;
	cmd->strs = NULL;
	cmd->files = NULL;
	if (!_btree_cmd(cmd, list, shell))
		return (FALSE);
	*node = btree_create_node(cmd);
	if (!*node)
		return (wati_error(3, "alloc fail"));
	return (TRUE);
}

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_shell *shell);

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_shell *shell)
{
	while (*list && is_opercmd(get_token(*list)->oper))
	{
		if (!cmd_parse_token(cmd, list, shell))
		{
			free_cmd(cmd);
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell);

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_list	*new;

	token = (*list)->content;
	new = NULL;
	if (!is_opercmd(token->oper) || token->oper == P_IN)
		return (wati_error(2, "parse error near '%s'", get_token(*list)->str));
	if (token->oper == NO)
	{
		new = wati_lstnew(token->str);
		if (!new)
			return (wati_error(3, "alloc fail"));
		wati_lstadd_back(&cmd->strs, new);
		(*list) = (*list)->next;
		return (TRUE);
	}
	return (cmd_parse_redirect(cmd, list, shell));
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_token	*name;

	token = (*list)->content;
	if (!(*list)->next || !(*list)->next->content)
		return (wati_error(2, "parse error near '\\n'", token->str));
	free(token->str);
	(*list) = (*list)->next;
	name = (*list)->content;
	if (name->oper != NO)
		return (wati_error(2,
				"parse error near '%s'", name->str));
	(*list) = (*list)->next;
	if (token->oper == R_IN)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == R_OUT)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == H_IN)
		return (add_fd(&cmd->files, token->oper,
				here_doc(name->str, shell)));
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
