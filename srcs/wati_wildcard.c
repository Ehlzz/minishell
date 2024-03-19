/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:45:52 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/19 17:59:26 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

int	wildcard(char *wildcard)
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
		if (str)
		{
			list = wati_lstnew(str);
			if (list)
				wati_lstadd_back(&strs, list);
		}
		entry = readdir(dir);
	}
	return (strs);
}
