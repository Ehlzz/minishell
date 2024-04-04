/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 17:33:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	t_list	*lst;
// 	t_list	*env;

// 	(void)argc;
// 	env = env_getlist(envp);
// 	set_readline_signal();
// 	while (1)
// 	{
// 		str = wati_readline(env, argv[0]);
// 		if (str == NULL)
// 			break ;
// 		if (wati_strlen(str) == 4 && !wati_strncmp(str, "exit", 4))
// 			break ;
// 		lst = init_parsing(str, env);
// 		if (lst)
// 			wati_lstclear(&lst, free);
// 	}
// 	if (str)
// 		free(str);
// 	wati_lstclear(&env, free);
// 	return (0);
// }

int	find_stars(char *str)
{
	if (!str)
		return (0);
	if (str && *str == '*')
		return (1);
	if (str && str[wati_strlen(str)] == '*')
		return (3);
	while (*str)
	{
		if (*str == '*')
			return (2);
		str++;
	}
	return (0);
}


/*

TWO CASE :

1 : * at the start
2 : * after the start

* at the start of the word = The end is compared.
* after the start = The start is compared too

*/

static char	*get_first_check(char *search)
{
	char	*str0;
	int		len;

	str0 = search;
	while (search && *search && *search != '*')
		search++;
	len = search - str0;
	return (wati_substr(str0, 0, len));
}

static char	*get_second_check(char *search)
{
	while (search && *search && *search != '*')
		search++;
	if (*search == '*')
		search++;
	return (search);
}

int is_valid(char *content, char *search)
{
	int	star_emplacement;
	int	search_len;
	
	(void)content;
	star_emplacement = find_stars(search);
	if (star_emplacement == 1)
	{
		while (*search == '*')
			search++;
		search_len = wati_strlen(search);
		while (*content)
		{
			if (!wati_strncmp(content, search, search_len) && wati_strlen(content) >= wati_strlen(search))
				return (1);
			content++;
		}
		return (0);
	}
	else if (star_emplacement == 2)
	{
		/*
		Save the content until the star and verify which file match with the start.
		After check if the content match with the end and return 1 if its works.
		*/
		char	*first_check;
		char	*second_check;
		int		first_check_len;
		int		second_check_len;

		first_check = get_first_check(search);
		first_check_len = wati_strlen(first_check);
		second_check = get_second_check(search);
		second_check_len = wati_strlen(second_check);
		if (wati_strncmp(content, first_check, first_check_len))
		{
			free(first_check);
			return (0);	
		}
		while (*content)
		{
			if (!wati_strncmp(content, second_check, second_check_len) && wati_strlen(content) >= wati_strlen(second_check))
			{
				free(first_check);
				return (1);
			}
			content++;
		}
		free(first_check);
		return (0);	
	}
	if (star_emplacement == 3)
	{
		char	*first_check;
		int		first_check_len;

		first_check = get_first_check(search);
		first_check_len = wati_strlen(first_check);
		if (!wati_strncmp(content, first_check, first_check_len))
		{
			free(first_check);
			return (1);	
		}
		free(first_check);
		return (0);
	}
	return (0);
}

t_list	*wildcard_search(t_list *lst, char *search)
{
	t_list	*lst0;
	t_list	*new_lst;

	lst0 = lst;
	new_lst = NULL;
	while (lst)
	{
		if (is_valid(lst->content, search))
			wati_lstadd_back(&new_lst, wati_lstnew(wati_strdup(lst->content)));
		lst = lst->next;
	}
	wati_lstclear(&lst0, free);
	return (new_lst);
}

int	main(int argc, char **argv)
{
	t_list	*test;
	t_list	*test2;
	char	*wildcard_str;
	
	if (argc <= 1)
		return (1);
	test = wildcard(argv[1]);	
	wati_putchar_fd('\n', 2);
	wati_putendl_fd("BEFORE", 2);
	wati_putchar_fd('\n', 2);
	wati_lstiter(test, print);
	wildcard_str = argv[2];
	test2 = wildcard_search(test, wildcard_str);
	wati_putchar_fd('\n', 2);
	wati_putendl_fd("AFTER", 2);
	wati_putchar_fd('\n', 2);
	wati_lstiter(test2, print);
	wati_lstclear(&test2, free);
	printf("\nsearch : %s\n", wildcard_str);
	return (0);
}


/*
* = Tous les fichiers,
x* = Tous les fichiers, commencant par x,
*x = Tous les fichiers finnissant par x,
x*x = tous les fichiers contenant x n'importe quoi et x,


SEARCH = *.c

List : 
.
..
dir
builtin
parse
signal_new.c
environnement
wati_readline.c
env
main_ehlz.c
libwati
wati_wildcard.c
wati_prompt.c

Mouvement :

. -- Not correct, skipped, lst = lst->next
.. -- Not correct, skipped, lst = lst->next
dir -- Not correct, skipped, lst = lst->next
builtin -- Not correct, skipped, lst = lst->next
parse -- Not correct, skipped, lst = lst->next
signal_new.c -- Correct, saved, first element of the new list
environnement -- Not correct, skipped, lst = lst->next
wati_readline.c -- Correct, saved, second element of the new list
env -- Not correct, skipped, lst = lst->next
main_ehlz.c -- Correct, saved, third element of the new list
libwati -- Not correct, skipped, lst = lst->next
wati_wildcard.c -- Correct, saved, fourth element of the new list
wati_prompt.c -- Correct, saved, fifth element of the new list

*/


