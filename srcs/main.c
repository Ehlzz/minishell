/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/11 21:29:26 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

char	*remove_quote(char *str);

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
		wati_lstiter(lst, print_token);
		root = NULL;
		btree_build(&root, lst);
		btree_apply_by_level(root, print_cmd_by_level);
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
		lst = init_parsing(str, env);;
		add_history(str);
		free(str);
		root = NULL;
		btree_build(&root, lst);
		btree_apply_by_level(root, print_cmd_by_level);
		btree_clear(root, free_cmd);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
