/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:51:39 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 17:51:48 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_available(char *str)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
		{
			quote = *str;
			str++;
		}
		if (*str == quote)
		{
			quote = 0;
			str++;
			continue ;
		}
		str++;
		i++;
	}
	return (i);
}

char	*remove_quote(char *str)
{
	char	*result;
	char	*str0;
	int		i;
	int		quote;

	result = malloc(count_available(str) + 1);
	str0 = str;
	i = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			result[i++] = *str;
		str++;
	}
	result[i] = '\0';
	free(str0);
	return (result);
}
