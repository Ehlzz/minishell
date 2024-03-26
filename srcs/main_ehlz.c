/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/26 15:29:53 by ehalliez         ###   ########.fr       */
=======
/*   Updated: 2024/03/23 15:37:53 by bedarenn         ###   ########.fr       */
>>>>>>> bedarenn2
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
<<<<<<< HEAD
	env_lst = create_env_list(env);
=======
	env = env_getlist(envp);
>>>>>>> bedarenn2
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
<<<<<<< HEAD
		{
			wati_lstiter(lst, free);
			wati_lstclean(&lst);
			if (!wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
				break ;
		}
		free(str);
=======
			wati_lstclear(&lst, free);
>>>>>>> bedarenn2
	}
	if (str)
		free(str);
	wati_lstclear(&env, free);
	return (0);
}
