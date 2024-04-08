/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:53:17 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/08 16:04:31 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>	
#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

static t_bool	parse_word(t_list **lst, t_list **l_strs, t_fds *fds);

t_cmd	*new_cmd(t_list **lst, t_fds fds)
{
	t_list		*list;
	t_cmd		*cmd;
	t_list		*l_strs;

	list = *lst;
	l_strs = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (list && in_command(list->content))
	{
		if (!parse_word(&list, &l_strs, &fds))
			break ;
	}
	cmd->strs = wati_lstsplit(l_strs);
	wati_lstclean(&l_strs);
	cmd->fds = fds;
	cmd->oper = NO;
	*lst = list;
	return (cmd);
}

t_bool	in_command(t_token *token)
{
	return (token->oper == NO
		|| token->oper == R_IN
		|| token->oper == R_OUT
		|| token->oper == H_IN
		|| token->oper == H_OUT);
}

static t_bool	redirecion(t_token *token, t_fds *fds, t_list **lst);

static t_bool	parse_word(t_list **lst, t_list **l_strs, t_fds *fds)
{
	t_list	*list;
	t_token	*token;

	list = *lst;
	token = get_token(list);
	if (token->oper == NO)
	{
		wati_lstadd_back(l_strs, wati_lstnew(get_token(list)->str));
		list = list->next;
	}
	else if (!redirecion(list->content, fds, &list))
		return (FALSE);
	*lst = list;
	return (TRUE);
}

static t_bool	redirecion(t_token *token, t_fds *fds, t_list **lst)
{
	free(token->str);
	if (token->oper == R_OUT)
		open_write(fds, (*lst)->next, O_WRONLY | O_CREAT | O_TRUNC);
	if (token->oper == H_OUT)
		open_write(fds, (*lst)->next, O_WRONLY | O_CREAT | O_APPEND);
	if (token->oper == R_IN)
		open_read(fds, (*lst)->next);
	if (fds->in < 0 || fds->out < 0)
		return (FALSE);
	(*lst) = (*lst)->next->next;
	return (TRUE);
}
