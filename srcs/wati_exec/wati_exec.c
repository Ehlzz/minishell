/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/24 12:54:57 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "minishell.h"

t_bool	wati_exec(t_btree *root, t_list *env)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = root->item;
	if (cmd->oper == NO)
	{
		pid = wati_execve(cmd, env, root);
		if (pid)
			waitpid(pid, NULL, 0);
	}
	return (TRUE);
}
