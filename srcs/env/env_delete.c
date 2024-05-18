/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:16:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/18 15:04:15 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	_env_delete(t_list	**env, t_string find);

void	env_delete(t_list	**env, t_string find)
{
	t_string	str;

	if (!env || !*env || !(*env)->content || !find || !*find)
		return ;
	str = wati_strjoin(find, "=");
	_env_delete(env, str);
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
