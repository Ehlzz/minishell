/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:52:03 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 19:03:51 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <wati_typedef.h>

#include "minishell.h"

int	g_err;

static t_bool	shell_build(t_shell *shell);
static void		env_checker(t_list **env);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
		return (wati_error(1, "can't read script : %s", argv[1]));
	shell.env = env_getlist(envp);
	env_checker(&shell.env);
	g_err = 0;
	while (shell_build(&shell))
		;
	wati_lstclear(&shell.env, free);
	return (0);
}

static void	_env_checker(t_list **env)
{
	int		shlvl;
	char	*search;
	char	*tmp;

	search = env_search(*env, "SHLVL");
	if (search)
	{
		shlvl = wati_atoi(search);
		shlvl++;
		tmp = wati_itoa(shlvl);
		free(search);
		search = wati_strjoin("SHLVL=", tmp);
		free(tmp);
		env_add(env, search);
	}
	else
		env_add(env, wati_strdup("SHLVL=1"));
}

static void	env_checker(t_list **env)
{
	char	*current_dir;
	char	*search;

	current_dir = getcwd(NULL, 0);
	search = env_search(*env, "PWD");
	if (!search)
	{
		search = wati_strjoin("PWD=", current_dir);
		env_add(env, search);
	}
	else
		free(search);
	free(current_dir);
	search = env_search(*env, "OLDPWD");
	if (!search)
		env_add(env, wati_strdup("OLDPWD"));
	else
		free(search);
	_env_checker(env);
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
