/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 12:56:55 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void	open_read(t_fds *fds, t_list *list)
{
	t_word	*word;
	t_fd	fd;

	if (!list)
	{
		wati_fprintf(2, "Error: no file given\n");
		if (fds->in > 2)
			close(fds->in);
		fds->in = -1;
		return ;
	}
	word = list->content;
	if (word->oper != NO)
		wati_fprintf(2, "Error: syntax error near unexpected token '%s'\n",
			word->str);
	fd = open(word->str, O_RDONLY);
	if (fd < 0)
	{
		if (access(word->str, F_OK))
			wati_fprintf(2, "Error: permission denied: %s\n",
				word->str);
		else
			wati_fprintf(2, "Error: no such file or directory: %s\n",
				word->str);
	}
	if (fds->in > 2)
		close(fds->in);
	fds->in = fd;
	free(word->str);
}
