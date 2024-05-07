/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:18:26 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/07 17:01:44 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

t_cmd	*get_cmd(t_btree *node)
{
	return (node->item);
}

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;

	cmd = ptr;
	if (cmd->strs)
		wati_lstclear(&cmd->strs, free);
	if (cmd->files.r_in)
		free(cmd->files.r_in);
	if (cmd->files.h_in > 2)
		close(cmd->files.h_in);
	if (cmd->files.r_out)
		free(cmd->files.r_out);
	if (cmd->files.h_out)
		free(cmd->files.h_out);
	free(cmd);
}

void	free_exec(void *ptr)
{
	t_exec	*exec;

	exec = ptr;
	free(exec->envp);
	wati_free_tab(exec->strs);
	free(exec->path);
}
