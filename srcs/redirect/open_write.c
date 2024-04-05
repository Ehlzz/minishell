/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:40 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/05 14:22:43 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_write(t_fds *fds, t_list *list, int flags)
{
	t_token	*token;
	t_fd	fd;

	if (!list)
	{
		wati_fprintf(STDERR_FILENO, "Error: no file given\n");
		if (fds->out > 2)
			close(fds->out);
		fds->out = -1;
		return ;
	}
	token = list->content;
	if (token->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"Error: syntax error near unexpected token '%s'\n",
			token->str);
	fd = open(token->str, flags, 0644);
	if (fd < 0)
		wati_fprintf(STDERR_FILENO, "Error: permission denied: %s\n",
			token->str);
	if (fds->out > 2)
		close(fds->out);
	fds->out = fd;
	free(token->str);
}
