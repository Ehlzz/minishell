/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/18 14:12:36 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <wati_typedef.h>

#include "minishell.h"

int	g_err;

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_shell	shell;
	t_bool	is_work;

	shell.env = env_getlist(envp);
	g_err = 0;
	if (argc != 1)
	{
		str = argv[1];
		shell.list = init_parsing(str);
		shell.root = NULL;
		wati_lstiter(shell.list, print_token);
		wati_printf("\n-----\n");
		is_work = btree_build(&shell.root, shell.list, &shell);
		wati_lstclear(&shell.list, free);
		if (is_work)
		{
			btree_apply_by_level(shell.root, print_cmd_by_level);
			wati_printf("\n-----\n");
			wati_exec(&shell);
			btree_clear(shell.root, free_cmd);
		}
		else
			wati_fprintf(2, "EXEC_NOTHING\n");
		wati_lstclear(&shell.env, free);
		return (0);
	}
	while (1)
	{
		set_readline_signal();
		str = wati_readline(shell.env);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(shell.env);
		}
		if (str == NULL)
			break ;
		add_history(str);
		shell.list = init_parsing(str);
		free(str);
		shell.root = NULL;
		wati_lstiter(shell.list, print_token);
		wati_printf("\n-----\n");
		is_work = btree_build(&shell.root, shell.list, &shell);
		wati_lstclear(&shell.list, free);
		if (is_work)
		{
			btree_apply_by_level(shell.root, print_cmd_by_level);
			wati_printf("\n-----\n");
			wati_exec(&shell);
			btree_clear(shell.root, free_cmd);
		}
		else
			wati_fprintf(2, "EXEC_NOTHING\n");
	}
	wati_lstclear(&shell.env, free);
	return (0);
}
