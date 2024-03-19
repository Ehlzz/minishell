/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/19 18:25:41 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		wati_strlen(str);
		if (!str)
			break ;
		if (wati_strlen(str) == 4 && !wati_strncmp(str, "exit", 4))
			break ;
		lst = init_parsing(str, env);
		if (lst)
			wati_lstclear(&lst, free);
	}
	if (str)
		free(str);
	wati_lstclear(&env, free);
	return (0);
}
