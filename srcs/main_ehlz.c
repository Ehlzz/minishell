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





int is_valid(char *content, char *search)
{
	static int	i = 1;
	
	(void)content;
	(void)search;
	i++;
	return (i % 2); 
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
	wati_lstiter(test, print);
	wildcard_str = argv[2];
	test2 = wildcard_search(test, wildcard_str);
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