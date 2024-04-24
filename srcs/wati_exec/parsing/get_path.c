/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:06:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/23 16:38:15 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

static char	*lf_path(t_string *paths, t_string cmd);

t_string	get_path(t_string cmd, t_list *env)
{
	t_string	*paths;
	t_string	path;

	path = env_search(env, "PATH");
	if (!path)
		return (NULL);
	paths = wati_split(path, ':');
	if (!paths)
		return (NULL);
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
