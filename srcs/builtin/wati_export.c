/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:20:58 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/20 16:53:33 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*add_quote(char *str)
// {
// 	int		i;
// 	int		len;
// 	char	*str0;
// 	char	*result;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	str0 = str;
// 	len = wati_strlen(str);
// 	result = malloc(len + 3);
// 	if (!result)
// 		return (NULL);
// 	while (*str && *str != '=')
// 	{
// 		result[i] = *str;
// 		str++;
// 		i++;
// 	}
// 	result[i] = 0;
// 	if (!*str)
// 	{
// 		wati_printf("%s\n", result);
// 		return (result);
// 	}
// 	result[i] = '=';
// 	if (*str == '"')
// 		str++;
// 	result[i + 1]= '"';
// 	i++;
// 	str++;
// 	while (*str)
// 	{
// 		i++;
// 		result[i] = *str;
// 		str++;
// 	}
// 	result[i + 1] = '"';
// 	result[i + 2] = 0;
// 	wati_printf("%s\n", result);
// 	return (result);
// }

// void	add_to_env(char *str, t_list **env)
// {
// 	int	len;

// 	len = wati_strlen(str);
// 	add_quote(str);
// 	if (str && env)
// 		wati_lstadd_back(env, wati_lstnew(str));
// }

char	*__export_getline(char *str)
{
	char	*result;

	result = wati_strjoin("declare -x ", str);
	return (result);
}

void	export_sortlist(t_list **export)
{
	int	finish;
	char	*tmp;
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
				tmp = ptr1->next->content;
				ptr1->next->content = ptr1->content;
				ptr1->content = tmp;
				finish = 0;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
}

t_list	*export_getlist(t_list *env)
{
	t_list	*export;
	char	*str;
	t_list	*new;

	export = NULL;
	if (!env)
		return (export);
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
	return (export);
}

int	main(int argc, char **argv, char **envp)
{
	// char	*str;
	// t_list	*lst;
	t_list	*env;
	t_list	*export;

	env = env_getlist(envp);
	export = export_getlist(env);
	// set_readline_signal();
	// (void)argc;
	// while (1)
	// {
	// 	str = wati_readline(env, argv[0]);
	// 	add_history(str);
	// 	while (str != NULL && *str == '\0')
	// 	{
	// 		free(str);
	// 		str = wati_readline(env, argv[0]);
	// 	}
	// 	if (str == NULL)
	// 		break ;
	// 	lst = init_parsing(str, env);
	// 	add_to_env(lst->content, &env);
	// 	wati_env(env);
	// 	wati_lstiter(lst, print);
	// 	wati_lstclear(&lst, free);
	// }
	export_sortlist(&export);
	wati_lstiter(export, print);
	wati_lstclear(&env, free);
	wati_lstclear(&export, free);
	// return (0);
	// add_to_env(argv[1], &env);
	// wati_env(env);
}
