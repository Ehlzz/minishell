/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:32:55 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 17:53:01 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_to_dollar(char *line, int i)
{
	char	*str;
	char	quote;
	int		len;
	int		dollar_count;

	str = line;
	dollar_count = 0;
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
		if (quote != '\'' && *str == '$' && dollar_count == i)
			break ;
		if (quote != '\'' && *str == '$')
			dollar_count++;
		str++;
	}
	len = str - line;
	return (wati_substr(line, 0, len));
}

char	*dollar_to_dollar(char *line, int i)
{
	char	*str;
	int		len_start;
	int		len_end;
	int		dollar_count;

	str = line;
	dollar_count = 0;
	while (str && *str)
	{
		if (*str == '$' && dollar_count == i)
			break ;
		if (*str == '$')
			dollar_count++;
		str++;
	}
	len_start = str - line;
	str++;
	while (*str && (wati_isalnum(*str) || *str == '_' || *str == '?'))
		str++;
	len_end = str - line;
	return (wati_substr(line, len_start, len_end - len_start));
}

char	*__dollar_to_end(char *line, char *str)
{
	while (*str && (wati_isalnum(*str) || *str == '_' || *str == '?'))
		str++;
	return (wati_substr(line, str - line, wati_strlen(line)));
}

char	*dollar_to_end(char *line, int i)
{
	char	*str;
	char	quote;
	int		dollar_count;

	str = line;
	quote = 0;
	dollar_count = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
		{
			quote = *str;
			str++;
		}
		if (*str == quote)
			quote = 0;
		if (quote != '\'' && *str == '$' && dollar_count == i)
			break ;
		if (quote != '\'' && *str == '$')
			dollar_count++;
		str++;
	}
	if (*str == '$')
		str++;
	return (__dollar_to_end(line, str));
}
