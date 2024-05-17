/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:48:21 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 18:03:49 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <dirent.h>

t_list	*__get_current_dir(DIR *dir, t_list *strs)
{
	closedir(dir);
	return (strs);
}

t_list	*get_current_dir(void)
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
		else
			free(str);
		entry = readdir(dir);
	}
	return (__get_current_dir(dir, strs));
}
