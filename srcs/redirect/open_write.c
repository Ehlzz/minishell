/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:40 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 12:47:33 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_write(t_fds *fds, t_list *list, int flags)
{
	t_token	*token;

	if (fds->out > 2)
		close(fds->out);
	fds->out = -1;
	if (!list)
	{
		wati_error("no file given");
		return ;
	}
	token = list->content;
	if (token->oper != NO)
		wati_error("syntax error near unexpected token '%s'", token->str);
	else
	{
		fds->out = open(token->str, flags, 0644);
		if (fds->out < 0)
			wati_error("permission denied: %s", token->str);
	}
}
