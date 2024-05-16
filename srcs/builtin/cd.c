/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:31 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 18:04:31 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wati_chdir(t_list **env, const t_string dir_name)
{
	char	*new_dir;

	if (!env || !*env)
		return ;
	new_dir = get_dir(env, dir_name);
	new_dir = check_tild(new_dir, *env);
	if (!new_dir)
		return ;
	if (is_directory(new_dir) > 0)
	{
		chdir(new_dir);
		update_pwd(env);
	}
	else
		wati_fprintf(2, "cd: %s: No such file or directory\n", dir_name);
	free(new_dir);
}
