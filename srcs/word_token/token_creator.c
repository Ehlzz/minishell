/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:53:17 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 15:12:06 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>	
#include <unistd.h>

#include "minishell.h"

static t_bool	in_command(t_list *list);
static t_bool	parse_word(t_list **lst, t_list **l_strs, t_fds *fds);

t_token	*new_token(t_list **lst, t_fds fds)
{
	t_list		*list;
	t_token		*token;
	t_list		*l_strs;

	list = *lst;
	l_strs = NULL;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->fds = fds;
	while (in_command(list))
	{
		if (!parse_word(&list, &l_strs, &token->fds))
			break ;
	}
	token->strs = wati_lstsplit(l_strs);
	wati_lstclean(&l_strs);
	*lst = list;
	return (token);
}

static t_bool	in_command(t_list *list)
{
	return (list && (getc_word(list)->oper == NO
			|| getc_word(list)->oper == R_IN
			|| getc_word(list)->oper == R_OUT
			|| getc_word(list)->oper == H_OUT));
}

static t_bool	redirecion(t_word *word, t_fds *fds, t_list **lst,
	void (*f)(t_fds *fds, t_list *list))
{
	free(word->str);
	f(fds, (*lst)->next);
	if (fds->in < 0 || fds->out < 0)
		return (FALSE);
	(*lst) = (*lst)->next->next;
	return (TRUE);
}

static t_bool	parse_word(t_list **lst, t_list **l_strs, t_fds *fds)
{
	t_list	*list;
	t_word	*word;

	list = *lst;
	word = getc_word(list);
	if (word->oper == NO)
	{
		wati_lstadd_back(l_strs, wati_lstnew(getc_word(list)->str));
		list = list->next;
	}
	else if (word->oper == R_IN
		&& !redirecion(list->content, fds, &list, &open_read))
		return (FALSE);
	else if (word->oper == R_OUT
		&& !redirecion(list->content, fds, &list, &open_write_trunc))
		return (FALSE);
	else if (word->oper == H_OUT
		&& !redirecion(list->content, fds, &list, &open_write_append))
		return (FALSE);
	*lst = list;
	return (TRUE);
}
