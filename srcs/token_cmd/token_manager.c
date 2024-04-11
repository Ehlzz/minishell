/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/11 20:08:23 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

int	len_without_quote(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str != c)
			len++;
		str++;
	}
	return (len);
}

char	*remove_quote(char *str)
{
	int		i;
	char	*result;
	char	quote;

	if (*str != '\'' && *str != '"')
		return (str);
	quote = *str;
	i = 0;
	result = malloc(len_without_quote(str, quote) + 1);
	while (*str)
	{
		if (*str != quote)
		{
			result[i] = *str;
			i++;
		}
		str++;
	}
	return (result);
}

t_token	*new_token(t_string str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = remove_quote(str);
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

	if (!ptr)
	{
		printf("NCMD\n");
		return ;
	}
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
