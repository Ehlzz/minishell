/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:06:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/09 16:47:01 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

static char	*lf_path(t_string *paths, t_string cmd);
static char	*lf_current(t_string cmd);

t_string	get_path(t_string cmd, t_list *env)
{
	t_string	*paths;
	t_string	path;

	path = lf_current(cmd);
	paths = NULL;
	if (path)
		return (path);
	path = env_search(env, "PATH");
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
	path = lf_path(paths, cmd);
	wati_free_tab(paths);
	return (path);
}

static char	*lf_path(t_string *paths, t_string cmd)
{
	char	*str;

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
