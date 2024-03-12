/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/12 17:25:28 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	print(void *ptr)
{
	char	*str;

	str = ptr;
	printf("%s ", str);
}

int	main(void)
{
	char	*str;
	t_list	*list;

	while (1)
	{
		str = readline("minishell> ");
		list = parsing(str);
		wati_lstiter(list, print);
		printf("\n");
		wati_lstclear(&list, free);
		free(str);
	}
	return (0);
}
