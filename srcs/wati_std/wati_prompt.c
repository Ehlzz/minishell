/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:38 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 15:39:05 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

static char	*get_format_pwd(t_list *env);

char	*wati_prompt(t_list *env)
{
	char	*str;
	char	*user;
	char	*pwd;

	user = env_search(env, "USER");
	pwd = get_format_pwd(env);
	str = wati_joinf(12, BLUE, user, DEFAULT, "@",
			B_CYAN, NAME, DEFAULT, " ",
			B_PURPLE, pwd, DEFAULT, " $ ");
	free(user);
	free(pwd);
	return (str);
}

static char	*get_format_pwd(t_list *env)
{
	char	*str;
	char	*pwd;
	char	*home;
	size_t	len;

	pwd = env_search(env, "PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	home = env_search(env, "HOME");
	if (!home)
		return (pwd);
	len = wati_strlen(home);
	if (wati_strncmp(home, pwd, len))
	{
		free(home);
		return (pwd);
	}
	str = wati_strjoin("~", pwd + len);
	free(pwd);
	free(home);
	return (str);
}
