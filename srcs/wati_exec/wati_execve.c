/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/17 12:22:09 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

t_bool	_execve(char **argv, t_shell *shell);
void	__execve(t_exec exec, t_list *env);
t_bool	exec_builtin(t_exec exec, t_list *env);
int		is_builtin(char *path);

void	__wati_execve(t_exec exec, t_shell *shell, t_list **pids)
{
	if (is_builtin(*exec.strs))
		exec_builtin(exec, shell->env);
	else if (exec.path)
		__execve(exec, shell->env);
	else
	{
		error_code = 127;
		free(exec.path);
	}
	wati_free_tab(exec.strs);
	wati_lstclear(&shell->env, free);
	btree_clear(shell->root, free_cmd);
	if (*pids)
		wati_lstclear(pids, free);
	exit(error_code);
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
			wati_dup_files(cmd->files, fd);
			__wati_execve(exec, shell, pids);
		}
		if (pid)
			add_pid(pids, pid);
	}
	wati_free_tab(exec.strs);
	return (TRUE);
}
