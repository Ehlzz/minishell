/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 15:52:22 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
		if (lst)
		{
			wati_lstiter(lst, free);
			wati_lstclean(&lst);
			if (!wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
				break ;
		}
		free(str);
			wati_lstclear(&lst, free);
	}
	if (str)
		free(str);
	wati_lstclear(&env, free);
	return (0);
}
