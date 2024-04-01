/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:18:26 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 16:04:52 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

t_cmd	*get_cmd(t_btree *node)
{
	return (node->item);
}

void	print_cmd(void *ptr)
{
	t_cmd		*cmd;
	t_string	*strs;

	cmd = ptr;
	strs = cmd->strs;
	while (*strs)
	{
		wati_putstr_fd(*strs, 1);
		wati_putchar_fd(' ', 1);
		strs++;
	}
	wati_putstr_fd("fd: ", 1);
	wati_putnbr_fd(cmd->fds.in, 1);
	wati_putchar_fd(' ', 1);
	wati_putnbr_fd(cmd->fds.out, 1);
}

void	free_cmd(t_cmd *cmd)
{
	wati_free_tab(cmd->strs);
	if (cmd->fds.in > 2)
		close(cmd->fds.in);
	if (cmd->fds.out > 2)
		close(cmd->fds.out);
	free(cmd);
}
