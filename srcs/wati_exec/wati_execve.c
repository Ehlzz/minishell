/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:30:59 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

pid_t	wati_execve(t_cmd *cmd, t_pipe *fd, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	pid = fork();
	if (!pid)
	{
		exec.path = get_path(cmd->strs->content, shell->env);
		exec.strs = wati_lstsplit(cmd->strs);
		exec.envp = wati_lstsplit(shell->env);
		wati_dup_files(cmd->files, fd);
		close_spipe(*fd);
		if (exec.path && exec.envp)
			execve(exec.path, exec.strs, exec.envp);
		free(exec.path);
		free(exec.strs);
		free(exec.envp);
		btree_clear(shell->root, free_cmd);
		wati_lstclear(&shell->env, free);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
