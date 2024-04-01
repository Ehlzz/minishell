/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 15:47:44 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_read(t_fds *fds, t_list *list)
{
	t_token	*token;
	t_fd	fd;

	if (!list)
	{
		wati_fprintf(STDERR_FILENO,
			"Error: no file given\n");
		if (fds->in > 2)
			close(fds->in);
		fds->in = -1;
		return ;
	}
	token = list->content;
	if (token->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"Error: syntax error near unexpected token '%s'\n",
			token->str);
	fd = open(token->str, O_RDONLY);
	if (fd < 0)
	{
		if (access(token->str, F_OK))
			wati_fprintf(STDERR_FILENO, "Error: permission denied: %s\n",
				token->str);
		else
			wati_fprintf(STDERR_FILENO,
				"Error: no such file or directory: %s\n",
				token->str);
	}
	if (fds->in > 2)
		close(fds->in);
	fds->in = fd;
	free(token->str);
}
