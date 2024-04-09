/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:24:22 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/27 14:51:37 by bedarenn         ###   ########.fr       */
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

void	env_print(t_list *env)
{
	wati_lstiter(env, print_endl);
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

	if (!env || !*env || !(*env)->content)
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
