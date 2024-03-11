/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 19:20:13 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libwati.h>

void print(void *str)
{
	wati_putendl_fd(str, 1);
}

int	main(int argc, char **argv)
{
	t_list *lst;
	
	(void)argc;
	lst = NULL;	
	wati_lstadd_back(&lst, wati_lstnew(argv[1]));
	wati_lstiter(lst, print);
	return (0);
}
