/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:30:16 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/15 11:01:30 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_no(t_cmd *cmd);

void	print_cmd(void *ptr)
{
	t_cmd	*cmd;

	if (!ptr)
	{
		wati_putendl_fd("NO CMD", 1);
		return ;
	}
	cmd = ptr;
	fprint_operator(cmd->oper, 1);
	wati_putchar_fd(' ', 1);
	if (cmd->oper == NO)
		print_no(cmd);
	wati_putchar_fd('\n', 1);
}

void	print_cmd_by_level(void *ptr, int level, int is_first_elem)
{
	while (level > 0)
	{
		wati_putchar_fd('\t', 1);
		level--;
	}
	if (is_first_elem == 0)
		wati_putstr_fd("->", 1);
	print_cmd(ptr);
}

void	print_n(void *str)
{
	wati_putstr_fd(str, 1);
	wati_putchar_fd(' ', 1);
}

static void	print_file(void *ptr);

static void	print_no(t_cmd *cmd)
{
	if (cmd->strs)
		wati_lstiter(cmd->strs, print_n);
	wati_putstr_fd("files: ", 1);
	if (cmd->files)
		wati_lstiter(cmd->files, print_file);
}

static void	print_file(void *ptr)
{
	t_file	*file;

	file = ptr;
	if (file->fd > 0)
	{
		wati_putnbr_fd(file->fd, 1);
		wati_putchar_fd(' ', 1);
	}
	if (file->name)
	{
		wati_putstr_fd(file->name, 1);
		wati_putchar_fd(' ', 1);
	}
}
