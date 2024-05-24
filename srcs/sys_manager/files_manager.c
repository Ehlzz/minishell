/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:12:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/24 15:56:37 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

t_bool	add_file(t_list **files, t_oper oper, t_string name)
{
	t_file	*file;
	t_list	*new;

	file = malloc(sizeof(t_file));
	if (!file)
		return (FALSE);
	file->oper = oper;
	file->name = name;
	file->fd = -1;
	new = wati_lstnew(file);
	if (!new)
	{
		free(file);
		return (FALSE);
	}
	wati_lstadd_back(files, new);
	return (TRUE);
}

t_bool	add_fd(t_list	**files, t_oper oper, t_fd fd)
{
	t_file	*file;
	t_list	*new;

	if (fd <= 2)
		return (FALSE);
	file = malloc(sizeof(t_file));
	if (!file)
		return (FALSE);
	file->oper = oper;
	file->fd = fd;
	file->name = NULL;
	new = wati_lstnew(file);
	if (!new)
	{
		free(file);
		return (FALSE);
	}
	wati_lstadd_back(files, new);
	return (TRUE);
}
