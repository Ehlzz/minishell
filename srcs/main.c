/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/13 17:04:05 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_shell	shell;
	t_bool	is_work;

	shell.env = env_getlist(envp);
	if (argc != 1)
	{
		str = argv[1];
		lst = init_parsing(str);
		shell.root = NULL;	
		wati_lstiter(lst, print_token);
		wati_printf("\n-----\n");
		is_work = btree_build(&shell.root, lst);
		wati_lstclear(&lst, free);
		if (is_work)
		{
			btree_apply_by_level(shell.root, print_cmd_by_level);
			wati_printf("\n-----\n");
			wati_exec(shell);
			btree_clear(shell.root, free_cmd);
		}
		wati_lstclear(&shell.env, free);
		return (0);
	}
	set_readline_signal();
	while (1)
	{
		str = wati_readline(shell.env);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(shell.env);
		}
		if (str == NULL)
			break ;
		add_history(str);
		lst = init_parsing(str);
		free(str);
		shell.root = NULL;
		is_work = btree_build(&shell.root, lst);
		wati_lstclear(&lst, free);
		if (is_work)
		{
			btree_apply_by_level(shell.root, print_cmd_by_level);
			wati_printf("-----\n");
			wati_exec(shell);
			btree_clear(shell.root, free_cmd);
		}
		else
			btree_clear(shell.root, free_cmd);
	}
	wati_lstclear(&shell.env, free);
	return (0);
}
