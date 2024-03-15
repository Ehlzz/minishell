/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/15 19:23:13 by ehalliez         ###   ########.fr       */
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
	while (1)
	{
		str = readline("minish> ");
		lst = init_parsing(str, env_lst);
		if (lst)
		{
			wati_lstiter(lst, print);
			wati_lstiter(lst, free);
			wati_lstclean(&lst);
			if (!wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
				break ;
		}
	}
	free(str);
	argv++;
	wati_putstr_fd(find_environment_variable(env_lst, *argv + 1), 1);
	wati_lstclean(&env_lst);

	return (0);
}
