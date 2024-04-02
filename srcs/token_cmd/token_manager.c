/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/02 14:24:35 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

t_token	*new_token(t_string str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->oper = is_operator(str);
	return (token);
}

t_token	*get_token(t_list *list)
{
	return (list->content);
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
	else if (token->oper == P_IN)
		printf("P_IN\n");
	else if (token->oper == P_OUT)
		printf("P_OUT\n");
	else if (token->oper == NO)
		printf("NO : %s\n", token->str);
	else
		printf("Error : %s\n", token->str);
}
