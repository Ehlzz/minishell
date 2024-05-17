/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:16:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 19:43:46 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__env_delete(t_list	*list)
{
	t_list		*next;

	if (list && list->next && list->next->next)
	{
		next = list->next;
		list->next = list->next->next;
		wati_lstdelone(next, free);
		return ;
	}
	if (list && list->next)
	{
		next = list->next;
		list->next = NULL;
		wati_lstdelone(next, free);
	}
}

void	env_delete(t_list	**env, t_string find)
{
	t_string	str;
	t_list		*list;
	t_list		*next;

	if (!env || !*env || !(*env)->content || !find || !*find)
		return ;
	str = wati_strjoin(find, "=");
	list = get_vat_prev_w_equal(*env, str);
	if (!list->next)
		list = get_vat_prev(*env, find);
	if (!wati_strncmp(str, list->content, wati_strlen(str)))
	{
		next = list;
		list = list->next;
		free(str);
		return ;
	}
	free(str);
	return (__env_delete(list));
}
