/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:20 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 16:39:51 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_operator(char *s)
{
	if (!wati_memcmp(s, "&&", 2))
		return (wati_strdup("&&"));
	else if (!wati_memcmp(s, "||", 2))
		return (wati_strdup("||"));
	else if (!wati_memcmp(s, "<<", 2))
		return (wati_strdup("<<"));
	else if (!wati_memcmp(s, ">>", 2))
		return (wati_strdup(">>"));
	else if (*s == '|')
		return (wati_strdup("|"));
	else if (*s == '<')
		return (wati_strdup("<"));
	else if (*s == '>')
		return (wati_strdup(">"));
	return (NULL);
}

t_oper	is_operator(char *s)
{
	if (!wati_memcmp(s, "&&", 2))
		return (AND);
	else if (!wati_memcmp(s, "||", 2))
		return (OR);
	else if (!wati_memcmp(s, "<<", 2))
		return (H_IN);
	else if (!wati_memcmp(s, ">>", 2))
		return (H_OUT);
	else if (*s == '|')
		return (PIPE);
	else if (*s == '<')
		return (R_IN);
	else if (*s == '>')
		return (R_OUT);
	return (NO);
}
