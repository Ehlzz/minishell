/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:43:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 19:23:26 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int	is_exec(t_string path)
{
	if (!access(path, X_OK) && is_directory(path) <= 0)
		return (GOOD);
	if (is_directory(path) > 0)
		return (IS_DIR);
	else if (!access(path, F_OK))
		return (PERM_DENIED);
	return (NO_EXIST);
}

t_bool	path_error(int errr, t_string cmd)
{
	if (errr == IS_DIR)
		return (wati_error(126, "is a directory: %s", cmd));
	else if (errr == PERM_DENIED)
		return (wati_error(126, "permission denied: %s", cmd));
	else if (errr == NO_EXIST)
		return (wati_error(127, "no such file or directory: %s", cmd));
	return (TRUE);
}

t_bool	lf_path_error(t_string *path,
	int *last_errr, t_string *last_path)
{
	int	errr;

	errr = is_exec(*path);
	if (errr == GOOD)
	{
		free(*last_path);
		return (TRUE);
	}
	else if (errr == PERM_DENIED)
	{
		free(*last_path);
		*last_path = *path;
		*last_errr = errr;
	}
	else
		free(*path);
	return (FALSE);
}

t_bool	paths_error(int errr, t_string path, t_string cmd)
{
	if (errr == PERM_DENIED)
	{
		wati_error(126, "permission denied: %s", path);
		free(path);
		return (FALSE);
	}
	return (wati_error(127, "command not found: %s", cmd));
}
