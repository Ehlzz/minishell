/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:32:55 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/11 19:20:45 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_to_dollar(char *line)
{
	char	*str;
	int		len;

	str = line;
	while (str && *str && *str != '$')
		str++;
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
	while (*str && *str != ' ' && *str != '$')
		str++;
	len_end = str - line;
	if (!*str)
		len_end--;
	return (wati_substr(line, len_start, len_end - len_start));
}

char	*dollar_to_end(char *line)
{
	char	*str;
	int		len;

	str = line;
	while (*str != '$')
		str++;
	while (*str)
	{
		str++;
		if (*str == ' ' || *str == '$')
			break ;
	}
	if (*line == '"')
	{
		if (*str)
			len = str - line;
		else
			len = str - line - 1;
	}
	else
		len = str - line;
	return (wati_substr(line, len, wati_strlen(line)));
}

char	*modify_token(char *line, t_list *env_lst)
{
	char	*start;
	char	*variable;
	char	*end;
	char	*tmp;
	int		dollar_count;

	dollar_count = count_dollars(line);
	while (dollar_count)
	{
		start = start_to_dollar(line);
		if (*line == '"')
			variable = find_variable(env_lst, dollar_to_dollar(line));
		else
			variable = find_variable(env_lst, line);
		tmp = wati_strjoin(start, variable);
		start = tmp;
		end = dollar_to_end(line);
		tmp = wati_strjoin(tmp, end);
		free(start);
		line = tmp;
		dollar_count--;
	}
	return (line);
}

char	*verify_token(char *line, t_list *env_lst)
{
	char	*str0;
	char	*str;
	bool	simple_quote;
	bool	double_quote;

	str0 = line;
	str = str0;
	simple_quote = false;
	double_quote = false;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && (!simple_quote && !double_quote))
		{
			if (*str == '\'')
				simple_quote = true;
			if (*str == '"')
				double_quote = true;
		}
		str++;
	}
	if (!simple_quote)
		return (modify_token(line, env_lst));
	return (line);
}
