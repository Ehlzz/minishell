/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/19 13:15:03 by ehalliez         ###   ########.fr       */
=======
/*   Updated: 2024/04/20 12:19:43 by bedarenn         ###   ########.fr       */
>>>>>>> origin/bedarenn
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

void	free_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = ptr;
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
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
