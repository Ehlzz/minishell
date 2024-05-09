/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/09 17:07:54 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

t_bool	_execve(char **argv, t_list **env);
void	__execve(char *path, char **argv, char **envp);

t_bool	wati_execve(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;
	t_list	*lst;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	lst = convert_strs(cmd->strs, shell->env);
	exec.strs = wati_lstsplit(lst);
	if (!_execve(exec.strs, &shell->env))
	{
		pid = fork();
		if (!pid)
		{
			exec.path = get_path(cmd->strs->content, shell->env);
			exec.envp = wati_lstsplit(shell->env);
			wati_dup_files(cmd->files, fd);
			close_spipe(*fd);
			if (exec.path && exec.envp)
				__execve(exec.path, exec.strs, exec.envp);
			free_exec(&exec);
			btree_clear(shell->root, free_cmd);
			wati_lstclear(&shell->env, free);
			wati_lstclear(&shell->pids, free);
			wati_lstclean(&lst);
			exit(EXIT_FAILURE);
		}
		if (pids)
			add_pid(pids, pid);
	}
	wati_free_tab(exec.strs);
	wati_lstclean(&lst);
	return (TRUE);
}

static int	is_builtin(char *path)
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
		export(env, *(argv + 1));
	else
		return (FALSE);
	return (TRUE);
}

void	__execve(char *path, char **argv, char **envp)
{
	int	id;

	id = is_builtin(path);
	if (id == ECHO)
		wati_echo(argv);
	else if (id == PWD)
		print_pwd();
	else if (id == ENV)
		env_print(envp);
	else
		execve(path, argv, envp);
}
