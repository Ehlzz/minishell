/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:29:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 18:18:40 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libwati.h"
#include "wati_typedef.h"

t_list	*get_var_not_assigned(const t_list *list, t_string find)
{
	size_t	len;

	len = wati_strlen(find);
	while (list)
	{
		if (!wati_memcmp(find, list->content, len) && \
			len == wati_strlen(list->content))
			break ;
		list = list->next;
	}
	return ((t_list *)list);
}

t_list	*get_var(const t_list *list, t_string find)
{
	size_t	len;

	find = wati_strjoin(find, "=");
	if (!find)
		return (NULL);
	len = wati_strlen(find);
	while (list)
	{
		if (!wati_memcmp(find, list->content, len))
			break ;
		list = list->next;
	}
	free(find);
	return ((t_list *)list);
}

t_string	get_name(const t_string str)
{
	t_string	name;
	size_t		len;

	len = wati_strlen_set(str, '=');
	name = wati_substr(str, 0, len);
	return (name);
}

t_list	*get_vat_prev(const t_list *list, t_string find)
{
	size_t	len;

	if (!list)
		return (NULL);
	len = wati_strlen(find);
	if (list)
	{
		if (!wati_memcmp(find, list->content, len) && \
			wati_strlen(list->content) == len)
			return ((t_list *)list);
	}
	while (list->next)
	{
		if (!wati_memcmp(find, list->next->content, len) && \
			wati_strlen(list->next->content) == len)
			break ;
		list = list->next;
	}
	return ((t_list *)list);
}

t_list	*get_vat_prev_w_equal(const t_list *list, t_string find)
{
	size_t	len;

	if (!list)
		return (NULL);
	len = wati_strlen(find);
	if (list)
	{
		if (!wati_memcmp(find, list->content, len))
			return ((t_list *)list);
	}
	while (list->next)
	{
		if (!wati_memcmp(find, list->next->content, len))
			break ;
		list = list->next;
	}
	return ((t_list *)list);
}
