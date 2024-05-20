/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:16:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 11:15:23 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	_env_delete(t_list	**env, t_string find, t_string find_op);

void	env_delete(t_list	**env, t_string *finds)
{
	t_string	find_op;

	finds++;
	while (*finds)
	{
		find_op = wati_strjoin(*finds, "=");
		_env_delete(env, *finds, find_op);
		free(find_op);
		finds++;
	}
}

static void	_env_delete(t_list	**env, t_string find, t_string find_op)
{
	t_list	**prev;
	t_list	*list;
	size_t	size;
	size_t	size_op;

	list = *env;
	prev = env;
	size = wati_strlen(find);
	size_op = wati_strlen(find_op);
	while (list
		&& wati_strncmp(list->content, find, wati_strlen(find))
		&& wati_strncmp(list->content, find_op, wati_strlen(find_op)))
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
