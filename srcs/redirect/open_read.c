/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 12:46:38 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_read(t_fds *fds, t_list *list)
{
	t_token	*token;

	if (fds->in > 2)
		close(fds->in);
	fds->in = -1;
	if (!list)
	{
		wati_error("no file given");
		return ;
	}
	token = list->content;
	if (token->oper == NO)
	{
		fds->in = open(token->str, O_RDONLY);
		if (fds->in < 0)
		{
			if (access(token->str, F_OK))
				wati_error("permission denied: %s", token->str);
			else
				wati_error("no such file or directory: %s", token->str);
		}
	}
	else
		wati_error("syntax error near unexpected token '%s'", token->str);
}
