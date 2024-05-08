/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:20:58 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/08 15:02:37 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_quote(char *str)
{
	int		i;
	int		len;
	char	*str0;
	char	*result;

	i = 0;
	str0 = str;
	len = wati_strlen(str) + 2;
	result = malloc(len + 1);
	while (*str && *str != '=')
	{
		result[i] = *str;
		i++;
		str++;
	}
	result[i] = *str;
	i++;
	str++;
	result[i] = '"';
	i++;
	while (*str)
	{
		result[i] = *str;
		i++;
		str++;
	}
	result[i] = '"';
	result[i + 1] = 0;
	free(str0);
	return (result);
}

char	*__export_getline(char *str)
{
	char	*result;

	result = wati_strjoin("declare -x ", str);
	return (add_quote(result));
}

void	swap_content(t_list **export)
{
	t_list  *ptr1;
	char	*tmp;

	ptr1 = *export;
	tmp = ptr1->next->content;
	ptr1->next->content = ptr1->content;
	ptr1->content = tmp;
}

void	export_sortlist(t_list **export)
{
	int		finish;
    t_list  *ptr1;
    t_list  *ptr2;

    if (*export == NULL)
        return ;
    ptr2 = NULL;
	finish = 0;
	while (!finish)
	{
		finish = 1;
		ptr1 = *export;
		while (ptr1->next != ptr2)
		{
			if (wati_strncmp(ptr1->content, ptr1->next->content, wati_strlen(ptr1->content) + 1) > 0)
			{
				swap_content(&ptr1);
				finish = 0;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
}

void	export_getlist(t_list *env)
{
	t_list	*export;
	char	*str;
	t_list	*new;

	export = NULL;
	if (!env)
		return ;
	while (env)
	{
		if (env->content)
		{
			str = __export_getline(env->content);
			new = wati_lstnew(str);
			if (new)
				wati_lstadd_back(&export, new);
		}
		env = env->next;
	}
	export_sortlist(&export);
	wati_lstiter(export, print);
	wati_lstclear(&export, free);
}

int		strlen_to_char(char *str, int c)
{
	int	i;

	i =	0;
	while (*str++ && *str != c)
		i++;
	if (*str == c)
		i++;
	return (i);
}

void	export(t_list *env, char **strs)
{
	if (!strs[1])
		return (export_getlist(env));
	env_add(&env, wati_strdup(strs[1]));
}
