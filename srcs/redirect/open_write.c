/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:40 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 15:21:47 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_write_trunc(t_fds *fds, t_list *list)
{
	t_word	*word;
	t_fd	fd;

	if (!list)
	{
		wati_fprintf(STDERR_FILENO, "Error: no file given\n");
		if (fds->out > 2)
			close(fds->out);
		fds->out = -1;
		return ;
	}
	word = list->content;
	if (word->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"Error: syntax error near unexpected token '%s'\n",
			word->str);
	fd = open(word->str, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		wati_fprintf(STDERR_FILENO, "Error: permission denied: %s\n",
			word->str);
	}
	if (fds->out > 2)
		close(fds->out);
	fds->out = fd;
	free(word->str);
}

void	open_write_append(t_fds *fds, t_list *list)
{
	t_word	*word;
	t_fd	fd;

	if (!list)
	{
		wati_fprintf(STDERR_FILENO, "Error: no file given\n");
		if (fds->out > 2)
			close(fds->out);
		fds->out = -1;
		return ;
	}
	word = list->content;
	if (word->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"Error: syntax error near unexpected token '%s'\n",
			word->str);
	fd = open(word->str, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
	{
		wati_fprintf(STDERR_FILENO, "Error: permission denied: %s\n",
			word->str);
	}
	if (fds->out > 2)
		close(fds->out);
	fds->out = fd;
	free(word->str);
}
