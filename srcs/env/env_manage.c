/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:24:22 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 22:50:23 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

t_list	*env_getlist(t_string *envp)
{
	t_list		*list;
	t_string	str;
	t_list		*new;

	list = NULL;
	if (!envp)
		return (list);
	while (*envp)
	{
		str = wati_strdup(*envp);
		if (str)
		{
			new = wati_lstnew(str);
			if (new)
				wati_lstadd_back(&list, new);
		}
		envp++;
	}
	return (list);
}

t_string	env_search(t_list *env, t_string var)
{
	t_list		*list;
	t_string	str;

	list = get_var(env, var);
	if (!list || !list->content)
		return (NULL);
	str = wati_strdup(list->content + wati_strlen(var) + 1);
	return (str);
}

t_list	*env_add(t_list **env, t_string str)
{
	t_string	name;
	t_list		*new;

	name = get_name(str);
	if (!str)
		return (NULL);
	new = get_var(*env, name);
	if (!new)
		new = get_var_not_assigned(*env, name);
	free(name);
	if (new)
	{
		if (new->content)
			free(new->content);
		new->content = str;
	}
	else
	{
		new = wati_lstnew(str);
		if (new)
			wati_lstadd_back(env, new);
	}
	return (new);
}

void	env_delete(t_list	**env, t_string find)
{
	t_string	str;
	t_list		*list;
	t_list		*next;

	if (!env || !*env || !(*env)->content || !find || !*find)
		return ;
	str = wati_strjoin(find, "=");
	if (!wati_memcmp(str, (*env)->content, wati_strlen((*env)->content)))
	{
		next = (*env);
		(*env) = (*env)->next;
		wati_lstdelone(next, free);
		return ;
	}
	free(str);
	list = get_vat_prev(*env, find);
	if (list)
	{
		next = list->next;
		list->next = list->next->next;
		wati_lstdelone(next, free);
	}
}
