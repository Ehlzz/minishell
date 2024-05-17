/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:18:26 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 14:45:26 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

t_cmd	*get_cmd(t_btree *node)
{
	return (node->item);
}

static void	free_file(void *ptr);

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;

	cmd = ptr;
	if (cmd->strs)
		wati_lstclear(&cmd->strs, free);
	if (cmd->files)
		wati_lstclear(&cmd->files, free_file);
	free(cmd);
}

static void	free_file(void *ptr)
{
	t_file	*file;

	file = ptr;
	if (file->fd > 2)
		wati_close(file->fd);
	if (file->name)
		free(file->name);
	free(file);
}

void	free_exec(void *ptr)
{
	t_exec	*exec;

	exec = ptr;
	free(exec->strs);
	free(exec->path);
}
