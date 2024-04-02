/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:18:26 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/02 15:13:18 by bedarenn         ###   ########.fr       */
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

	if (!ptr)
	{
		wati_putendl_fd("NO CMD", 1);
		return ;
	}
	cmd = ptr;
	fprint_operator(cmd->oper, 1);
	wati_putchar_fd(' ', 1);
	if (cmd->oper == NO)
	{
		strs = cmd->strs;
		if (strs)
		{
			while (*strs)
			{
				wati_putstr_fd(*strs, 1);
				wati_putchar_fd(' ', 1);
				strs++;
			}
		}
	}
	wati_putstr_fd("fd: ", 1);
	wati_putnbr_fd(cmd->fds.in, 1);
	wati_putchar_fd(' ', 1);
	wati_putnbr_fd(cmd->fds.out, 1);
	wati_putchar_fd('\n', 1);
}

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;

	cmd = ptr;
	if (cmd->strs)
		wati_free_tab(cmd->strs);
	if (cmd->fds.in > 2)
		close(cmd->fds.in);
	if (cmd->fds.out > 2)
		close(cmd->fds.out);
	free(cmd);
}
