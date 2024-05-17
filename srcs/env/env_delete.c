/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:16:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/17 13:38:45 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	__env_delete(t_list	*list)
// {
// 	t_list		*next;

// 	if (list && list->next && list->next->next)
// 	{
// 		next = list->next;
// 		list->next = list->next->next;
// 		wati_lstdelone(next, free);
// 		return ;
// 	}
// 	if (list && list->next)
// 	{
// 		next = list->next;
// 		list->next = NULL;
// 		wati_lstdelone(next, free);
// 	}
// }

// void	env_delete(t_list	**env, t_string find)
// {
// 	t_list		**list;
// 	t_string	str;

// 	if (!env || !*env || !(*env)->content || !find || !*find)
// 		return ;
// 	list = env;
// 	str = wati_strjoin(find, "=");
// 	list = get_vat_prev_w_equal(*env, str);
// 	if (!list->next)
// 		list = get_vat_prev(*env, find);
// 	if (!wati_strncmp(str, list->content, wati_strlen(str)))
// 	{
// 		next = list;
// 		list = list->next;
// 		free(str);
// 		return ;
// 	}
// 	free(str);
// 	return (__env_delete(list));
// }

void	_env_delete(t_list	**env, t_string find);

void	env_delete(t_list	**env, t_string find)
{
	t_string	str;

	if (!env || !*env || !(*env)->content || !find || !*find)
		return ;
	str = wati_strjoin(find, "=");
	_env_delete(env, find);
	free(str);
}

void	_env_delete(t_list	**env, t_string find)
{
	t_list	**prev;
	t_list	*list;
	int		size;

	list = *env;
	prev = env;
	size = wati_strlen(find);
	while (list && wati_strncmp(list->content, find, size))
	{
		prev = &list->next;
		list = list->next;
	}
	if (list)
	{
		*prev = list->next;
		free(list->content);
		free(list);
	}
}
