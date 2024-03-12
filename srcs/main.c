/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:41 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <readline/readline.h>

void	print(void *str)
{
	wati_putendl_fd(str, 1);
}

int	main(void)
{
	t_list	*list;
	char	*str;

	str = readline("test$ ");
	list = parsing("cat -e Makefile");
	wati_lstiter(list, print);
	wati_lstclear(&list, free);
	return (0);
}
