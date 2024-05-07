/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:12:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 15:46:27 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

t_files	files_build(t_string r_in, t_fd h_in,
	t_string r_out, t_string h_out)
{
	t_files	files;

	files.r_in = r_in;
	files.h_in = h_in;
	files.r_out = r_out;
	files.h_out = h_out;
	return (files);
}

t_bool	files_newin(t_files *files, t_string r_in, t_fd h_in)
{
	if ((r_in && h_in > 2) || (!r_in && h_in < 0))
		return (FALSE);
	if (files->r_in)
		free(files->r_in);
	if (files->h_in >= 2)
		close(files->h_in);
	files->r_in = NULL;
	files->h_in = -1;
	if (r_in)
		files->r_in = r_in;
	if (h_in > 2)
		files->h_in = h_in;
	return (TRUE);
}

t_bool	files_newout(t_files *files, t_string r_out, t_string h_out)
{
	if ((r_out && h_out) || (!r_out && !h_out))
		return (FALSE);
	if (files->r_out)
		free(files->r_out);
	if (files->h_out)
		free(files->h_out);
	files->r_out = NULL;
	files->h_out = NULL;
	if (r_out)
		files->r_out = r_out;
	if (h_out)
		files->h_out = h_out;
	return (TRUE);
}
