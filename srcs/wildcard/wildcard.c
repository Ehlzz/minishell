/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/14 15:50:29 by bedarenn         ###   ########.fr       */
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

void	__convert_strs(char *str, t_list **result)
{
	t_list	*wildcard;

	wildcard = wildcard_search(str);
	while (wildcard)
	{
		wati_lstadd_back(result, wati_lstnew(wati_strdup(wildcard->content)));
		wildcard = wildcard->next;
	}
	wati_lstclear(&wildcard, free);
}

t_list	*convert_strs(t_list *strs, t_list *env)
{
	t_list	*result;
	char	*str;

	result = NULL;
	while (strs)
	{
		str = (char *)strs->content;
		if (is_star(str))
		{
			__convert_strs(str, &result);
			strs = strs->next;
			continue ;
		}
		wati_lstadd_back(&result, \
		wati_lstnew(verify_token(wati_strdup(str), env)));
		strs = strs->next;
	}
	return (result);
}
