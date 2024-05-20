/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:06:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 20:33:21 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

int				is_builtin(char *path);

int				is_exec(t_string path);
t_bool			path_error(int errr, t_string cmd);
t_bool			paths_error(int errr, t_string path, t_string cmd);
t_bool			lf_path_error(t_string *path,
					int *last_errr, t_string *last_path);

static t_bool	lf_current(t_string *path, t_string cmd);
static t_bool	lf_relative(t_string *path, t_string cmd);
static t_bool	split_path(t_string **paths, t_list *env);
static t_bool	lf_path(t_string *path, t_string *paths, t_string cmd);

t_bool	get_path(t_string *path, t_string cmd, t_list *env)
{
	t_bool		r;
	t_string	*paths;

	*path = NULL;
	if (!wati_strncmp(cmd, "/", 1))
		return (lf_relative(path, cmd));
	if (!wati_strncmp(cmd, "./", 2)
		|| !wati_strncmp(cmd, "../", 3))
		return (lf_current(path, cmd));
	if (is_builtin(cmd))
	{
		*path = NULL;
		return (TRUE);
	}
	split_path(&paths, env);
	if (!paths)
		return (wati_error(127, "command not found: %s", cmd));
	r = lf_path(path, paths, cmd);
	wati_free_tab(paths);
	if (!r)
		*path = NULL;
	return (r);
}

static t_bool	lf_relative(t_string *path, t_string cmd)
{
	int	errr;

	errr = is_exec(cmd);
	if (errr == GOOD)
		*path = wati_strdup(cmd);
	return (path_error(errr, cmd));
}

static t_bool	lf_current(t_string *path, t_string cmd)
{
	t_string	str;
	int			errr;

	str = getcwd(NULL, 0);
	*path = wati_joinf(3, str, "/", cmd);
	free(str);
	errr = is_exec(*path);
	if (errr != GOOD)
	{
		free(*path);
		*path = NULL;
	}
	return (path_error(errr, cmd));
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
	int			last_errr;
	t_string	last_path;

	last_errr = NO_EXIST;
	last_path = NULL;
	while (*paths)
	{
		*path = wati_joinf(3, *paths, "/", cmd);
		if (lf_path_error(path, &last_errr, &last_path))
			return (TRUE);
		paths++;
	}
	return (paths_error(last_errr, *path, cmd));
}
