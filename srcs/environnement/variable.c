/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:56:35 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/18 19:21:47 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_variable(t_list *env_lst, char *to_find)
{
	int		len;
	char	*line;
	char	*variable;
	char	*str0;

	str0 = to_find;
	if (*to_find == '$')
		to_find++;
	while (env_lst)
	{
		variable = wati_strjoin(to_find, "=");
		len = wati_strlen(variable);
		line = env_lst->content;
		if (!wati_strncmp(line, variable, len))
		{
			free(variable);
			return (line + len);
		}
		free(variable);
		env_lst = env_lst->next;
	}
	return ("");
}
