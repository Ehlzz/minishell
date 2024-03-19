/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ehlz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/19 18:04:34 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_list	*lst;
	t_list	*env_lst;

	(void)argc;
	env_lst = create_env_list(env);
	// wati_lstiter(env_lst, print);
	set_readline_signal();
	while (1)
	{
		str = readline("minish> ");
		if (!str)
			break ;
		lst = init_parsing(str, env_lst);
		if (lst)
		{
			// wati_lstiter(lst, print);
			wati_lstiter(lst, free);
			wati_lstclean(&lst);
			if (!wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
				break ;
		}
		free(str);
	}
	if (str)
		free(str);
	argv++;
	wati_putstr_fd(find_environment_variable(env_lst, *argv + 1), 1);
	wati_lstclean(&env_lst);
	return (0);
}
