/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/24 13:13:01 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	wati_execve(t_cmd *cmd, t_list *env, t_btree *root)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd || !cmd->strs || !*cmd->strs || !**cmd->strs)
		return (0);
	pid = fork();
	if (!pid)
	{
		exec.path = get_path(*cmd->strs, env);
		exec.strs = cmd->strs;
		exec.envp = wati_lstsplit(env);
		dup_fds(cmd->fds);
		if (exec.path && exec.envp)
			execve(exec.path, exec.strs, exec.envp);
		free(exec.path);
		free(exec.envp);
		btree_clear(root, free_cmd);
		wati_lstclear(&env, free);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}
