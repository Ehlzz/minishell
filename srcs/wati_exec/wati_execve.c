/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 14:36:50 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

t_bool		_execve(char **argv, t_shell *shell);
void		__execve(t_exec exec, t_list *env);
t_bool		exec_builtin(t_exec exec, t_list *env);
int			is_builtin(char *path);
static void	execve_free(t_exec exec, t_pipe *fd, t_list **pids, t_shell *shell);

void	__wati_execve(t_exec exec, t_shell *shell)
{
	if (is_builtin(*exec.strs))
		exec_builtin(exec, shell->env);
	else if (exec.path)
		__execve(exec, shell->env);
	else
		g_err = 127;
}

t_bool	wati_execve_pipe(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;
	t_list	*lst;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	pid = 0;
	pid = fork();
	if (!pid)
	{
		lst = convert_strs(cmd->strs, shell->env);
		exec.path = NULL;
		exec.strs = wati_lstsplit(lst);
		wati_lstclean(&lst);
		if (!_execve(exec.strs, shell))
		{
			exec.path = get_path(*exec.strs, shell->env);
			if (exec.path && wati_dup_files(cmd->files, fd))
				__wati_execve(exec, shell);
		}
		execve_free(exec, fd, pids, shell);
	}
	if (pid)
		add_pid(pids, pid);
	return (TRUE);
}

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
	wati_lstclean(&lst);
	if (!_execve(exec.strs, shell))
	{
		pid = fork();
		if (!pid)
		{
			exec.path = get_path(*exec.strs, shell->env);
			if (exec.path && wati_dup_files(cmd->files, fd))
				__wati_execve(exec, shell);
			execve_free(exec, fd, pids, shell);
		}
		if (pid)
			add_pid(pids, pid);
	}
	wati_free_tab(exec.strs);
	return (TRUE);
}

static void	execve_free(t_exec exec, t_pipe *fd, t_list **pids, t_shell *shell)
{
	if (!exec.path)
		close_spipe(*fd);
	if (g_err)
		free(exec.path);
	wati_free_tab(exec.strs);
	wati_lstclear(&shell->env, free);
	btree_clear(shell->root, free_cmd);
	if (*pids)
		wati_lstclear(pids, free);
	exit(g_err);
}
