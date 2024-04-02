/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/02 15:33:35 by bedarenn         ###   ########.fr       */
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

	env = env_getlist(envp);
	if (argc != 1)
	{
		str = argv[1];
		lst = init_parsing(str, env);
		wati_lstiter(lst, &print_token);
		root = NULL;
		btree_build(&root, lst);
		wati_putendl_fd("-----", 1);
		btree_apply_infix(root, print_cmd);
		wati_putchar_fd('\n', 1);
		btree_clear(root, free_cmd);
		wati_lstclear(&lst, free);
		wati_lstclear(&env, free);
		return (0);
	}
	set_readline_signal();
	while (1)
	{
		str = wati_readline(env, argv[0]);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(env, argv[0]);
		}
		if (str == NULL)
			break ;
		lst = init_parsing(str, env);
		free(str);
		wati_lstiter(lst, &print_token);
		root = NULL;
		btree_build(&root, lst);
		wati_putendl_fd("-----", 1);
		btree_apply_infix(root, print_cmd);
		wati_putchar_fd('\n', 1);
		btree_clear(root, free_cmd);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
