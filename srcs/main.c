/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/23 15:58:20 by bedarenn         ###   ########.fr       */
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
	t_bool	is_work;

	env = env_getlist(envp);
	if (argc != 1)
	{
		str = argv[1];
		lst = init_parsing(str, env);
		root = NULL;
		is_work = btree_build(&root, lst);
		wati_lstclear(&lst, free);
		if (is_work)
		{
			btree_apply_by_level(root, print_cmd_by_level);
			wati_printf("-----\n");
			wati_exec(root, env);
			btree_clear(root, free_cmd);
		}
		else
			btree_clear(root, free_cmd);
		wati_lstclear(&env, free);
		return (0);
	}
	set_readline_signal();
	while (1)
	{
		str = wati_readline(env);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(env);
		}
		if (str == NULL)
			break ;
		lst = init_parsing(str, env);
		free(str);
		root = NULL;
		if (btree_build(&root, lst))
		{
			btree_apply_by_level(root, print_cmd_by_level);
			btree_clear(root, free_cmd);
		}
		else
			btree_clear(root, free_cmd);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
