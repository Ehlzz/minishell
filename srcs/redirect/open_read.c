/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/05 14:27:52 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

static void	print_error(t_string name);

void	open_read(t_fds *fds, t_list *list)
{
	t_token	*token;
	t_fd	fd;

	if (fds->in > 2)
		close(fds->in);
	fds->in = -1;
	if (!list)
	{
		wati_fprintf(STDERR_FILENO,
			"Error: no file given\n");
		return ;
	}
	token = list->content;
	if (token->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"Error: syntax error near unexpected token '%s'\n",
			token->str);
	fd = open(token->str, O_RDONLY);
	if (fd < 0)
		print_error(token->str);
	fds->in = fd;
	free(token->str);
}

static void	print_error(t_string name)
{
	if (access(name, F_OK))
		wati_fprintf(STDERR_FILENO, "Error: permission denied: %s\n",
			name);
	else
		wati_fprintf(STDERR_FILENO,
			"Error: no such file or directory: %s\n",
			name);
}
