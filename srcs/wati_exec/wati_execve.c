/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/30 20:12:56 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

pid_t	wati_execve(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd || !cmd->strs || !*cmd->strs || !**cmd->strs)
		return (0);
	pid = fork();
	if (!pid)
	{
		exec.path = get_path(*cmd->strs, shell->env);
		exec.strs = cmd->strs;
		exec.envp = wati_lstsplit(shell->env);
		wati_dup2(cmd->fds);
		wati_fprintf(2, "%s : %i->%i\n", *cmd->strs, cmd->fds.in, cmd->fds.out);
		if (exec.path && exec.envp)
			execve(exec.path, exec.strs, exec.envp);
		free(exec.path);
		free(exec.envp);
		btree_clear(shell->root, free_cmd);
		wati_lstclear(&shell->env, free);
		close(shell->fd.pipe[0]);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}
