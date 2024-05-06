/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:32:55 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/06 14:44:22 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_to_dollar(char *line)
{
	char	*str;
	char	quote;
	int		len;

	str = line;
	quote = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
		{
			quote = *str;
			str++;
		}
		if (*str == quote)
			quote = 0;
		if (quote != '\'' && *str == '$')
			break ;
		str++;
	}
	len = str - line;
	return (wati_substr(line, 0, len));
}

char	*dollar_to_dollar(char *line)
{
	char	*str;
	int		len_start;
	int		len_end;

	str = line;
	while (str && *str && *str != '$')
		str++;
	len_start = str - line;
	str++;
	while (*str && *str != ' ' && *str != '$' && *str != '\'' && *str != '"')
		str++;
	len_end = str - line;
	return (wati_substr(line, len_start, len_end - len_start));
}

char	*dollar_to_end(char *line)
{
	char	*str;
	char	quote;

	str = line;
	quote = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
		{
			quote = *str;
			str++;
		}
		if (*str == quote)
			quote = 0;
		if (quote != '\'' && *str == '$')
			break ;
		str++;
	}
	while (*str)
	{
		str++;
		if (*str == ' ' || *str == '$' || *str == '\'' || *str == '"')
			break ;
	}
	return (wati_substr(line, str - line, wati_strlen(line)));
}

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
