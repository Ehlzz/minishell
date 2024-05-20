/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 12:54:24 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

void	execve_free(t_exec exec, t_pipe *fd, t_list **pids, t_shell *shell);

t_string	*get_strs(t_list *cmd, t_list *env)
{
	t_list		*list;
	t_string	*strs;

	list = convert_strs(cmd, env);
	strs = wati_lstsplit(list);
	wati_lstclean(&list);
	return (strs);
}

static void	__wati_execve(t_exec exec, t_shell *shell)
{
	if (get_path(&exec.path, *exec.strs, shell->env)
		&& wati_dup_fds(exec.fds))
	{
		if (is_builtin(*exec.strs))
			exec_builtin(exec, shell->env);
		else if (exec.path)
			__execve(exec, shell->env);
		else
			g_err = 127;
	}
}

t_bool	wati_execve_pipe(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd)
		return (0);
	pid = 0;
	pid = fork();
	if (!pid)
	{
		if (!wati_dup_files(&exec.fds, cmd->files, fd, shell->env))
			exit(g_err);
		if (!cmd->strs || !cmd->strs->content)
		{
			close_fds(exec.fds);
			exit(g_err);
		}
		exec.path = NULL;
		exec.strs = get_strs(cmd->strs, shell->env);
		if (!_execve(exec.strs, fd, pids, shell))
			__wati_execve(exec, shell);
		execve_free(exec, fd, pids, shell);
	}
	add_pid(pids, pid);
	return (TRUE);
}

t_bool	wati_execve(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	pid = 0;
	if (!cmd)
		return (FALSE);
	if (!wati_dup_files(&exec.fds, cmd->files, fd, shell->env))
		return (FALSE);
	if (!cmd->strs || !cmd->strs->content)
		return (close_fds(exec.fds));
	exec.strs = get_strs(cmd->strs, shell->env);
	if (!_execve(exec.strs, fd, pids, shell))
	{
		pid = fork();
		if (!pid)
		{
			exec.path = NULL;
			__wati_execve(exec, shell);
			execve_free(exec, fd, pids, shell);
		}
		add_pid(pids, pid);
	}
	close_fds(exec.fds);
	wati_free_tab(exec.strs);
	return (TRUE);
}
