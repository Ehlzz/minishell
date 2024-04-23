/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/10 17:33:55 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

static void	print_error(t_string name);

void	open_read(t_fds *fds, t_list *list)
{
	t_token	*token;

	if (fds->in > 2)
		close(fds->in);
	fds->in = -1;
	if (!list)
	{
		wati_fprintf(STDERR_FILENO, "%s: Error: no file given\n", NAME);
		return ;
	}
	token = list->content;
	if (token->oper != NO)
		wati_fprintf(STDERR_FILENO,
			"%s: Error: syntax error near unexpected token '%s'\n",
			NAME, token->str);
	else
	{
		fds->in = open(token->str, O_RDONLY);
		if (fds->in < 0)
			print_error(token->str);
	}
}

static void	print_error(t_string file)
{
	if (access(file, F_OK))
		wati_fprintf(STDERR_FILENO, "%s: Error: permission denied: %s\n",
			NAME, file);
	else
		wati_fprintf(STDERR_FILENO,
			"%s: Error: no such file or directory: %s\n",
			NAME, file);
}
