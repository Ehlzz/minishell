/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:02:06 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/19 19:13:05 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <minishell.h>
#include <libwati.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int		is_directory(const char *dir_name);

void	wati_chdir(t_list **env, const char *dir_name)
{
	if (!env || !*env || !dir_name)
		return ;
	if (is_directory(dir_name) > 0)
	{
		chdir(dir_name);
		update_pwd(env);
	}
	else
		wati_fprintf(2, "cd: %s: No such file or directory\n", dir_name);
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

static int	is_directory(const char *dir_name)
{
	t_stat	buf;

	if (stat(dir_name, &buf) == -1)
		return (-1);
	return (S_ISDIR(buf.st_mode));
}