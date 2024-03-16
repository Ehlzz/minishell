/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:29:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/16 18:53:57 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>

void	print_endl(void *ptr)
{
	wati_putendl_fd((char *)ptr, 1);
}

t_list	*get_var(const t_list *list, char *find)
{
	size_t	len;

	find = wati_strjoin(find, "=");
	if (!find)
		return (NULL);
	len = wati_strlen(find);
	while (list && wati_memcmp(find, list->content, len))
		list = list->next;
	free(find);
	return ((t_list *)list);
}

char	*get_name(const char *str)
{
	char	*name;
	size_t	len;

	len = wati_strlen_set(str, '=');
	name = wati_substr(str, 0, len);
	return (name);
}

t_list	*get_vat_prev(const t_list *list, char *find)
{
	size_t	len;

	if (!list)
		return (NULL);
	find = wati_strjoin(find, "=");
	if (!find)
		return (NULL);
	len = wati_strlen(find);
	while (list->next && wati_memcmp(find, list->next->content, len))
		list = list->next;
	free(find);
	if (!list->next)
		return (NULL);
	return ((t_list *)list);
}
