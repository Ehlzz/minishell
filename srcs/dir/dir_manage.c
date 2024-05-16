/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:02:06 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 17:45:33 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "minishell.h"
#include "libwati.h"

char	*check_tild(char *dir, t_list *env)
{
	char	*new_dir;
	char	*home;

	if (!dir || dir[0] != '~')
		return (dir);
	home = env_search(env, "HOME");
	if (!home)
	{
		wati_fprintf(2, "cd: HOME not set\n");
		return (NULL);
	}
	new_dir = wati_strjoin(home, dir + 1);
	free(dir);
	free(home);
	return (new_dir);
}

char	*get_dir(t_list **env, const t_string dir_name)
{
	char	*new_dir;

	if (!dir_name)
	{
		new_dir = env_search(*env, "HOME");
		if (!new_dir)
		{
			wati_fprintf(2, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (dir_name[0] == '-' && !dir_name[1])
	{
		new_dir = env_search(*env, "OLDPWD");
		if (!new_dir)
		{
			wati_fprintf(2, "cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		return (wati_strdup(dir_name));
	return (new_dir);
}

void	update_pwd(t_list **env)
{
	char	*path;
	char	*var;

	path = getcwd(NULL, 0);
	var = wati_strjoin("PWD=", path);
	env_add(env, var);
	free(path);
}

void	print_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	wati_putendl_fd(path, 1);
	free(path);
}

int	is_directory(const t_string dir_name)
{
	t_stat	buf;

	if (stat(dir_name, &buf) == -1)
		return (-1);
	return (S_ISDIR(buf.st_mode));
}
