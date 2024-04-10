/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/10 13:04:48 by bedarenn         ###   ########.fr       */
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

void	free_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = ptr;
	if (token->str)
		free(token->str);
}

void	print_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
	{
		printf("NCMD\n");
		return ;
	}
	token = ptr;
	fprint_operator(token->oper, 1);
	if (token->oper == NO)
		wati_printf(" %s\n", token->str);
	else
		wati_putchar_fd('\n', 1);
}
