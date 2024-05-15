/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/15 12:42:54 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

static t_bool	_execve(char **argv, t_list **env);
static void		__execve(t_exec exec, t_list *env);
static t_bool	exec_builtin(t_exec exec, t_list *env, t_list *lst,
					t_shell *shell);
int				is_builtin(char *path);
extern int error_code;

t_bool	wati_execve(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;
	t_list	*lst;

	pid = 0;
	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	lst = convert_strs(cmd->strs, shell->env);
	exec.strs = wati_lstsplit(lst);
	if (!_execve(exec.strs, &shell->env))
	{
		pid = fork();
		if (!pid)
		{
			exec.path = get_path(*exec.strs, shell->env);
			wati_dup_files(cmd->files, fd);
			if (is_builtin(*exec.strs))
				exec_builtin(exec, shell->env, lst, shell);
			if (exec.path)
				__execve(exec, shell->env);
			free(exec.strs);
			free(exec.path);
			btree_clear(shell->root, free_cmd);
			wati_lstclear(&shell->env, free);
			if (*pids)
				wati_lstclear(pids, free);
			wati_lstclear(&lst, free);
			exit(EXIT_FAILURE);
		}
		if (pid)
			add_pid(pids, pid);
	}
	wati_free_tab(exec.strs);
	wati_lstclean(&lst);
	return (TRUE);
}

static t_bool	exec_builtin(t_exec exec, t_list *env, t_list *lst,
					t_shell *shell)
{
	int	id;

	id = is_builtin(*exec.strs);
	if (id == ECHO)
		wati_echo(exec.strs);
	else if (id == PWD)
		print_pwd();
	else if (id == ENV)
		env_print(env);
	else if (id == EXPORT)
		export(env, exec.strs);
	btree_clear(shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	wati_free_tab(exec.strs);
	wati_lstclean(&lst);
	exit(EXIT_SUCCESS);
	return (TRUE);
}

int	is_builtin(char *path)
{
	if (!wati_strncmp(path, "echo", wati_strlen(path)) \
			&& wati_strlen(path) == 4)
		return (ECHO);
	if (!wati_strncmp(path, "cd", wati_strlen(path)) \
			&& wati_strlen(path) == 2)
		return (CD);
	if (!wati_strncmp(path, "pwd", wati_strlen(path)) \
			&& wati_strlen(path) == 3)
		return (PWD);
	if (!wati_strncmp(path, "export", wati_strlen(path)) \
			&& wati_strlen(path) == 6)
		return (EXPORT);
	if (!wati_strncmp(path, "unset", wati_strlen(path)) \
			&& wati_strlen(path) == 5)
		return (UNSET);
	if (!wati_strncmp(path, "env", wati_strlen(path)) \
			&& wati_strlen(path) == 3)
		return (ENV);
	if (!wati_strncmp(path, "exit", wati_strlen(path)) \
			&& wati_strlen(path) == 4)
		return (EXIT);
	return (0);
}

t_bool	_execve(char **argv, t_list **env)
{
	int	id;

	id = is_builtin(*argv);
	if (id == CD)
		wati_chdir(env, *(argv + 1));
	else if (id == UNSET)
	{
		argv++;
		while (*argv)
		{
			env_delete(env, *argv);
			argv++;
		}
	}
	else if (id == EXPORT && *(argv + 1))
		export(*env, argv);
	else
		return (FALSE);
	return (TRUE);
}

static void	__execve(t_exec exec, t_list *env)
{
	exec.envp = wati_lstsplit(env);
	execve(exec.path, exec.strs, exec.envp);
}
