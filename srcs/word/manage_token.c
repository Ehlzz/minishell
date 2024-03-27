/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/27 15:06:08 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

t_token	*new_token(t_string word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!word)
		return (NULL);
	token->word = word;
	token->oper = is_operator(word);
	return (token);
}

void	print_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token->oper == AND)
		printf("AND\n");
	else if (token->oper == OR)
		printf("OR\n");
	else if (token->oper == H_IN)
		printf("H_IN\n");
	else if (token->oper == R_OUT)
		printf("R_OUT\n");
	else if (token->oper == PIPE)
		printf("PIPE\n");
	else if (token->oper == R_IN)
		printf("R_IN\n");
	else if (token->oper == R_IN)
		printf("R_OUT\n");
	else
		printf("NO : %s\n", token->word);
}
