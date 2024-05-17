/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:56:35 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/15 19:00:38 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	find_variable(t_list *env_lst, t_string to_find)
{
	int			len;
	t_string	line;
	t_string	variable;

	if (*to_find == '$')
		to_find++;
	if (!*to_find)
		return (wati_strdup("$"));
	if (*to_find == '?' && wati_strlen(to_find) == 1)
		return (wati_itoa(error_code));
	while (env_lst)
	{
		variable = wati_strjoin(to_find, "=");
		len = wati_strlen(variable);
		line = env_lst->content;
		if (!wati_strncmp(line, variable, len))
		{
			free(variable);
			return (wati_strdup(line + len));
		}
		free(variable);
		env_lst = env_lst->next;
	}
	return (wati_strdup(""));
}
