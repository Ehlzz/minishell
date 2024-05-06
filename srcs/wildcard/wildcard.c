/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/06 16:01:01 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <dirent.h>

t_list	*wildcard(void)
{
	DIR		*dir;
	t_dir	*entry;
	t_list	*strs;
	char	*str;
	t_list	*list;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	strs = NULL;
	entry = readdir(dir);
	while (entry)
	{
		str = wati_strdup(entry->d_name);
		if (str && *str != '.')
		{
			list = wati_lstnew(str);
			if (list)
				wati_lstadd_back(&strs, list);
		}
		entry = readdir(dir);
	}
	return (strs);
}

t_list	*wildcard_search(char *search)
{
	t_list	*start;
	t_list	*lst0;
	t_list	*new_lst;

	start = wildcard();
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
