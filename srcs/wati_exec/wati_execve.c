/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/07 16:48:01 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

void	_execve(const char *path, const char **argv, const char **envp);

pid_t	wati_execve(t_cmd *cmd, t_pipe *fd, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;
	t_list	*lst;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	pid = fork();
	if (!pid)
	{
		exec.path = get_path(cmd->strs->content, shell->env);
		lst = convert_strs(cmd->strs, shell->env);
		exec.strs = wati_lstsplit(lst);
		exec.envp = wati_lstsplit(shell->env);
		wati_dup_files(cmd->files, fd);
		close_spipe(*fd);
		if (exec.path && exec.envp)
			_execve(exec.path, exec.strs, exec.envp);
		free_exec(&exec);
		btree_clear(shell->root, free_cmd);
		wati_lstclean(&shell->env);
		wati_lstclean(&lst);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static int	is_builtin(char *path)
{
	if (!wati_strncmp(path, "echo", wati_strlen(path)))
		return (ECHO);
	if (!wati_strncmp(path, "cd", wati_strlen(path)))
		return (CD);
	if (!wati_strncmp(path, "pwd", wati_strlen(path)))
		return (PWD);
	if (!wati_strncmp(path, "export", wati_strlen(path)))
		return (EXPORT);
	if (!wati_strncmp(path, "unset", wati_strlen(path)))
		return (UNSET);
	if (!wati_strncmp(path, "env", wati_strlen(path)))
		return (ENV);
	if (!wati_strncmp(path, "exit", wati_strlen(path)))
		return (EXIT);
	return (0);
}

void	_execve(const char *path, const char **argv, const char **envp)
{
	int	id;

	id = is_builtin(path);
	if (id == ECHO)
	{
		wati_echo(argv);
	}
	else if (id == PWD)
		print_pwd();
	else if (id == ENV)
		env_print(envp);
	else
		execve(path, argv, envp);
}
