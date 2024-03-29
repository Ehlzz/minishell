/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:18:26 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 12:55:29 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

void	print_token(void *ptr)
{
	t_token		*token;
	t_string	*strs;

	token = ptr;
	strs = token->strs;
	while (*strs)
	{
		wati_putstr_fd(*strs, 1);
		wati_putchar_fd(' ', 1);
		strs++;
	}
	wati_putstr_fd("fd: ", 1);
	wati_putnbr_fd(token->fds.in, 1);
	wati_putchar_fd(' ', 1);
	wati_putnbr_fd(token->fds.out, 1);
}

t_token	*getc_token(t_btree *node)
{
	return (node->item);
}

void	free_token(t_token *token)
{
	wati_free_tab(token->strs);
	if (token->fds.in > 2)
		close(token->fds.in);
	if (token->fds.out > 2)
		close(token->fds.out);
	free(token);
}
