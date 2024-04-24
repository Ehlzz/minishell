/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:53:17 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/24 13:23:03 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>	
#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

static t_bool	parse_word(t_list **list, t_list **l_strs, t_fds *fds);
static t_cmd	*_new_cmd(t_list *l_strs, t_fds fds);

t_cmd	*new_cmd(t_list **list, t_fds fds)
{
	t_list	*l_strs;

	l_strs = NULL;
	while (*list && in_command((*list)->content))
	{
		if (!parse_word(list, &l_strs, &fds))
		{
			close_fds(fds);
			wati_lstclear(&l_strs, free);
			return (NULL);
		}
	}
	return (_new_cmd(l_strs, fds));
}

t_bool	in_command(t_token *token)
{
	return (token->oper == NO
		|| token->oper == R_IN
		|| token->oper == R_OUT
		|| token->oper == H_IN
		|| token->oper == H_OUT);
}

static t_bool	redirection(t_list **list, t_fds *fds);

static t_bool	parse_word(t_list **list, t_list **l_strs, t_fds *fds)
{
	t_list	*new;
	t_token	*token;

	token = (*list)->content;
	if (token->oper == NO)
	{
		new = wati_lstnew(get_token(*list)->str);
		if (!new)
			return (wati_error("alloc fail"));
		wati_lstadd_back(l_strs, new);
		(*list) = (*list)->next;
	}
	else if (!redirection(list, fds))
		return (FALSE);
	return (TRUE);
}

static t_bool	redirection(t_list **list, t_fds *fds)
{
	t_token	*token;

	token = (*list)->content;
	if (token->oper == R_OUT)
		open_write(fds, (*list)->next, O_WRONLY | O_CREAT | O_TRUNC);
	else if (token->oper == H_OUT)
		open_write(fds, (*list)->next, O_WRONLY | O_CREAT | O_APPEND);
	else if (token->oper == R_IN)
		open_read(fds, (*list)->next);
	if (fds->in < 0 || fds->out < 0)
		return (FALSE);
	free(get_token(*list)->str);
	free(get_token((*list)->next)->str);
	(*list) = (*list)->next->next;
	return (TRUE);
}

static t_cmd	*_new_cmd(t_list *l_strs, t_fds fds)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		wati_lstclear(&l_strs, free);
		close_fds(fds);
		wati_error("alloc fail");
		return (NULL);
	}
	cmd->strs = wati_lstsplit(l_strs);
	if (!cmd->strs)
	{
		free(cmd);
		wati_lstclear(&l_strs, free);
		close_fds(fds);
		wati_error("alloc fail");
		return (NULL);
	}
	wati_lstclean(&l_strs);
	cmd->fds = fds;
	cmd->oper = NO;
	return (cmd);
}
