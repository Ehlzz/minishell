/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_oper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:20 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/18 15:05:56 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	get_operator(t_string s)
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
	else if (*s == '(')
		return (wati_strdup("("));
	else if (*s == ')')
		return (wati_strdup(")"));
	return (NULL);
}

t_oper	is_operator(t_string s)
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
	else if (*s == '(')
		return (P_IN);
	else if (*s == ')')
		return (P_OUT);
	return (NO);
}

void	fprint_operator(t_oper oper, t_fd fd)
{
	if (oper == NO)
		return ;
	else if (oper == PIPE)
		wati_putstr_fd("PIPE", fd);
	else if (oper == AND)
		wati_putstr_fd("AND", fd);
	else if (oper == OR)
		wati_putstr_fd("OR", fd);
	else if (oper == R_IN)
		wati_putstr_fd("R_IN", fd);
	else if (oper == R_OUT)
		wati_putstr_fd("R_OUT", fd);
	else if (oper == H_IN)
		wati_putstr_fd("H_IN", fd);
	else if (oper == H_OUT)
		wati_putstr_fd("H_OUT", fd);
	else if (oper == P_IN)
		wati_putstr_fd("P_IN", fd);
	else if (oper == P_OUT)
		wati_putstr_fd("P_OUT", fd);
	else
		wati_putstr_fd("ERR", fd);
}
