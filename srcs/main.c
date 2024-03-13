/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/13 13:37:36 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	t_list	*lst;

	while (1)
	{
		str = readline("minish> ");
		lst = init_parsing(str);
		wati_lstiter(lst, print);
		wati_lstiter(lst, free);
		if (lst)
		{
			wati_lstclean(&lst);
			if (!wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
				break ;
		}
	}
	free(str);
	return (0);
}
