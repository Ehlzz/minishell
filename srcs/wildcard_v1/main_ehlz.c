/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/10 18:00:03 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	wildcard_checker(char *search, char *content)
{
	while (*search)
	{
		if (*search == '*')
		{
			while (*search == '*')
				search++;
			if (!*search)
				return (1);
			while (*content)
			{
				if (*content == *search)
					break ;
				content++;
			}
		}
		if (!*content || (*search != *content))
			return (0);
		search++;
		content++;
	}
	return (1);
}

t_list	*wildcard_search(t_list *lst, char *search)
{
	t_list	*lst0;
	t_list	*new_lst;

	lst0 = lst;
	new_lst = NULL;
	while (lst)
	{
		if (wildcard_checker(search, lst->content))
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
