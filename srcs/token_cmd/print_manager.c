/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:30:16 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:45:20 by bedarenn         ###   ########.fr       */
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

static void	print_no(t_cmd *cmd)
{
	if (cmd->strs)
		wati_lstiter(cmd->strs, print);
	wati_putstr_fd("files: ", 1);
	if (cmd->files.h_in > 2)
		wati_printf("i:%i ", cmd->files.h_in);
	if (cmd->files.r_in)
		wati_printf("i:%s ", cmd->files.r_in);
	if (cmd->files.h_out)
		wati_printf("o:%s", cmd->files.h_out);
	if (cmd->files.r_out)
		wati_printf("o:%s", cmd->files.r_out);
}
