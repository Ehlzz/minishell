/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:06:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 17:41:02 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int				is_builtin(char *path);

static t_bool	lf_current(t_string *path, t_string cmd);
static t_bool	split_path(t_string **paths, t_list *env);
static t_bool	lf_path(t_string *path, t_string *paths, t_string cmd);

static t_bool	get_path_return(t_string *path,
					t_string value, t_bool r);

t_bool	get_path(t_string *path, t_string cmd, t_list *env)
{
	t_bool		r;
	t_string	*paths;

	if (is_builtin(cmd))
		return (get_path_return(path, NULL, TRUE));
	if (lf_current(path, cmd))
	{
		if (!path)
			return (FALSE);
		return (TRUE);
	}
	paths = NULL;
	split_path(&paths, env);
	r = lf_path(path, paths, cmd);
	if (!r)
	{
		wati_free_tab(paths);
		*path = NULL;
	}
	return (r);
}

static t_bool	lf_current(t_string *path, t_string cmd)
{
	t_string	str;

	if (wati_strncmp(cmd, "./", 2)
		&& wati_strncmp(cmd, "../", 3))
		return (FALSE);
	str = getcwd(NULL, 0);
	*path = wati_joinf(3, str, "/", cmd);
	free(str);
	if (!access(*path, X_OK))
		return (TRUE);
	else
	{
		if (!access(*path, F_OK))
			wati_error(126, "permission denied: %s", cmd);
		else
			wati_error(127, "no such file or directory: %s", cmd);
		free(*path);
		*path = NULL;
		return (TRUE);
	}
	return (TRUE);
}

static t_bool	split_path(t_string **paths, t_list *env)
{
	t_string	path;

	path = env_search(env, "PATH");
	if (path)
	{
		*paths = wati_split(path, ':');
		free(path);
		if (!*paths)
			return (FALSE);
	}
	else
		*paths = NULL;
	return (TRUE);
}

static t_bool	lf_path(t_string *path, t_string *paths, t_string cmd)
{
	t_bool	no_right;

	if (!access(cmd, X_OK))
		return (get_path_return(path, wati_strdup(cmd), TRUE));
	no_right = FALSE;
	if (!access(cmd, F_OK))
		no_right = TRUE;
	if (paths)
	{
		while (*paths)
		{
			*path = wati_joinf(3, *paths, "/", cmd);
			if (!access(*path, X_OK))
				return (TRUE);
			if (!access(*path, F_OK))
				no_right = TRUE;
			free(*path);
			paths++;
		}
	}
	if (no_right)
		return (wati_error(126, "permission denied: %s", cmd));
	return (wati_error(127, "command not found: %s", cmd));
}

static t_bool	get_path_return(t_string *path, t_string value, t_bool r)
{
	*path = value;
	return (r);
}
