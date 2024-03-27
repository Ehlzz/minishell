/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/27 16:06:53 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_list	*env;

	(void)argc;
	env = env_getlist(envp);
	set_readline_signal();
	while (1)
	{
		str = wati_readline(env, argv[0]);
		if (str == NULL)
			break ;
		if (wati_strlen(str) == 4 && !wati_strncmp(str, "exit", 4))
			break ;
		lst = init_parsing(str, env);
		wati_lstiter(lst, print_token);
		if (lst && !wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
		{
			wati_lstclear(&lst, free);
			break ;
		}
		wati_lstclear(&lst, free);
	}
	if (str)
		free(str);
	wati_lstclear(&env, free);
	return (0);
}
