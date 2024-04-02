/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/01 14:21:33 by bedarenn         ###   ########.fr       */
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
		wati_lstiter(lst, &print_token);
		root = NULL;
		btree_build(&root, lst);
		if (root->left)
			print_cmd(root->left->item);
		print_cmd(root->item);
		if (root->right)
			print_cmd(root->right->item);
		wati_putchar_fd('\n', 1);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
