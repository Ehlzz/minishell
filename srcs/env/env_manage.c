/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:24:22 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 15:43:20 by ehalliez         ###   ########.fr       */
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
	if (!list)
	{
		list = get_var_not_assigned(env, var);
		if (!list)
			return (NULL);
		return (wati_strdup(list->content));
	}
	if (!list || !list->content)
		return (NULL);
	str = wati_strdup(list->content + wati_strlen(var) + 1);
	return (str);
}

t_list	*__env_add(char *str, t_list **env, t_list *new)
{
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
	if (new && !is_char_equal(str))
	{
		free(str);
		free(name);
		return (new);
	}
	free(name);
	new = __env_add(str, env, new);
	return (new);
}

void	print_endl(void *ptr)
{
	wati_putendl_fd((t_string)ptr, 1);
}
