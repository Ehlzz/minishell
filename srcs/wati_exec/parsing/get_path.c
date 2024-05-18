/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:06:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 17:37:10 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

static char	*lf_path(t_string *paths, t_string cmd);
static char	*lf_current(t_string cmd);
int			is_builtin(char *path);

t_string	*__get_path(t_string path, t_string *paths)
{
	if (path)
	{
		paths = wati_split(path, ':');
		if (!paths)
			return (NULL);
	}
	else
	{
		paths = malloc(sizeof(char *));
		if (!paths)
			return (NULL);
		*paths = NULL;
	}
	free(path);
	return (paths);
}

t_string	get_path(t_string cmd, t_list *env)
{
	t_string	*paths;
	t_string	path;

	if (is_builtin(cmd))
		return (cmd);
	path = lf_current(cmd);
	paths = NULL;
	if (path)
		return (path);
	path = env_search(env, "PATH");
	paths = __get_path(path, paths);
	if (!paths)
		return (NULL);
	path = lf_path(paths, cmd);
	wati_free_tab(paths);
	if (!path)
		g_err = 127;
	return (path);
}

static char	*lf_path(t_string *paths, t_string cmd)
{
	char	*str;

	if (cmd && !*cmd)
	{
		wati_error("command not found: ''");
		return (NULL);
	}
	if (*cmd && !access(cmd, X_OK))
		return (cmd);
	while (*paths)
	{
		str = wati_joinf(3, *paths, "/", cmd);
		if (!access(str, X_OK))
			return (str);
		free(str);
		paths++;
	}
	wati_error("command not found: %s", cmd);
	return (NULL);
}

static char	*lf_current(t_string cmd)
{
	t_string	path;
	t_string	str;

	if (wati_strncmp(cmd, "./", 2)
		&& wati_strncmp(cmd, "../", 3))
		return (NULL);
	path = getcwd(NULL, 0);
	str = wati_joinf(3, path, "/", cmd);
	free(path);
	if (!access(str, X_OK))
		return (str);
	else
		free(str);
	return (NULL);
}
