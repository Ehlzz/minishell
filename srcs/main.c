/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/28 17:51:15 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_btree	*root;
	t_list	*env;

	(void)argc;
	env = env_getlist(envp);
	set_readline_signal();
	while (1)
	{
		str = wati_readline(env, argv[0]);
		if (str == NULL)
			break ;
		lst = init_parsing(str, env);
		free(str);
		wati_lstiter(lst, print_word);
		if (lst && !wati_strncmp(str, "exit", 4) && wati_strlen(str) == 4)
		{
			wati_lstclear(&lst, free);
			break ;
		}
		btree_build(&root, lst);
		print_token(root->item);
		wati_putchar_fd('\n', 1);
		free_token(root->item);
		free(root);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
