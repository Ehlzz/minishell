/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_lstsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:34:47 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/15 15:32:13 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>

char	**wati_lstsplit(t_list *list)
{
	t_list	*lst0;
	char	**strs0;
	char	**strs;
	size_t	size;

	size = wati_lstsize(list);
	strs0 = malloc(sizeof(char *) * (size + 1));
	if (!strs0)
		return (NULL);
	strs0[size] = NULL;
	strs = strs0;
	lst0 = list;
	while (list)
	{
		*strs = list->content;
		list = list->next;
		strs++;
	}
	return (strs0);
}
