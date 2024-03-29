/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_oper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:20 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/28 17:49:14 by bedarenn         ###   ########.fr       */
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

void	print_word(void *ptr)
{
	t_word	*word;

	word = ptr;
	if (word->oper == AND)
		printf("AND\n");
	else if (word->oper == OR)
		printf("OR\n");
	else if (word->oper == H_IN)
		printf("H_IN\n");
	else if (word->oper == R_OUT)
		printf("R_OUT\n");
	else if (word->oper == PIPE)
		printf("PIPE\n");
	else if (word->oper == R_IN)
		printf("R_IN\n");
	else if (word->oper == R_IN)
		printf("R_OUT\n");
	else if (word->oper == P_IN)
		printf("P_IN\n");
	else if (word->oper == P_OUT)
		printf("P_OUT\n");
	else if (word->oper == NO)
		printf("NO : %s\n", word->str);
	else
		printf("Error : %s\n", word->str);
}
