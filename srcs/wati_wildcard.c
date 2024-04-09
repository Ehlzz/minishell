/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:45:52 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/09 16:57:46 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "minishell.h"

t_list	*wildcard(char *where)
{
	DIR		*dir;
	t_dir	*entry;
	t_list	*strs;
	char	*str;
	t_list	*list;

	dir = opendir(where);
	if (dir == NULL)
		return (NULL);
	strs = NULL;
	entry = readdir(dir);
	while (entry)
	{
		str = wati_strdup(entry->d_name);
		if (str)
		{
			list = wati_lstnew(str);
			if (list)
				wati_lstadd_back(&strs, list);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (strs);
}