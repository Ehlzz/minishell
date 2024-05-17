/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:20:58 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 18:51:00 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*__export_getline(char *str)
{
	char	*result;

	if (wati_strlen(str) == 1)
		return (wati_strjoin("declare -x ", str));
	result = wati_strjoin("declare -x ", str);
	return (add_quote(result));
}

void	swap_content(t_list **export)
{
	t_list	*ptr1;
	char	*tmp;

	ptr1 = *export;
	tmp = ptr1->next->content;
	ptr1->next->content = ptr1->content;
	ptr1->content = tmp;
}

void	export_sortlist(t_list **export)
{
	int		finish;
	t_list	*ptr1;
	t_list	*ptr2;

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
			if (wati_strncmp(ptr1->content, ptr1->next->content, \
					wati_strlen(ptr1->content) + 1) > 0)
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

// export test$USER=test NON FONCTIONNEL

void	export(t_list *env, char **strs)
{
	int	verif;

	if (!strs[1])
		return (export_getlist(env));
	strs++;
	verif = is_char_before_char(*strs, '+', '=');
	while (*strs)
	{
		if (!verif_identifier(*strs))
		{
			printf("bash: export: `%s': not a valid identifier\n", *strs);
			strs++;
			error_code = 1;
			continue ;
		}
		if (!verif)
			env_add(&env, verify_token(wati_strdup(*strs), env));
		else
			export_concat(env, *strs);
		strs++;
	}
}
