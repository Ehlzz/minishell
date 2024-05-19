/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/19 17:33:12 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <wati_typedef.h>

#include "minishell.h"

int	g_err;

static t_bool	shell_build(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
		return (wati_error(1, "can't read script : %s", argv[1]));
	shell.env = env_getlist(envp);
	g_err = 0;
	while (shell_build(&shell))
		;
	wati_lstclear(&shell.env, free);
	return (0);
}

static t_bool	shell_build(t_shell *shell)
{
	char	*str;
	t_bool	is_work;

	str = wati_readline(shell->env);
	if (str == NULL)
		return (FALSE);
	add_history(str);
	shell->list = init_parsing(str);
	free(str);
	shell->root = NULL;
	is_work = btree_build(&shell->root, shell->list, shell);
	wati_lstclear(&shell->list, free);
	if (is_work)
	{
		wati_exec(shell);
		btree_clear(shell->root, free_cmd);
	}
	return (TRUE);
}
