/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 21:21:44 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*wildcard_search(char *search)
{
	t_list	*start;
	t_list	*lst0;
	t_list	*new_lst;

	start = get_current_dir();
	lst0 = start;
	new_lst = NULL;
	while (start)
	{
		if (wildcard_checker(search, start->content))
			wati_lstadd_back(&new_lst, \
				wati_lstnew(wati_strdup(start->content)));
		start = start->next;
	}
	wati_lstclear(&lst0, free);
	if (!new_lst)
		wati_lstadd_back(&new_lst, wati_lstnew(wati_strdup(search)));
	return (new_lst);
}

int	is_star(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}
