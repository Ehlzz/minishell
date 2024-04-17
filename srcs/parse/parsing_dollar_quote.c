/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:32:55 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/17 20:00:54 by ehalliez         ###   ########.fr       */
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

// char	*verify_token(char *line, t_list *env_lst)
// {
// 	char	*str0;
// 	char	*str;
// 	bool	simple_quote;
// 	bool	double_quote;

// 	str0 = line;
// 	str = str0;
// 	simple_quote = false;
// 	double_quote = false;
// 	while (*str)
// 	{
// 		if ((*str == '\'' || *str == '"') && (!simple_quote && !double_quote))
// 		{
// 			if (*str == '\'')
// 				simple_quote = true;
// 			if (*str == '"')
// 				double_quote = true;
// 		}
// 		str++;
// 	}
// 	if (!simple_quote)
// 		return (modify_token(line, env_lst));
// 	return (line);
// }

#include <stdio.h>

char	*truc_raciste(char *str, char c)
{
	char	*new;
	char	*str0;
	int		len;
	int		i;

	len = wati_strlen(str) + 1;
	new = malloc(len + 1);
	str0 = str;
	i = 0;
	while (*str)
	{
		new[i] = *str;
		i++;
		str++;
	}
	new[i] = c;
	new[i + 1] = 0;
	free(str0);
	return (new); 
}

char	*verify_token(char *line, t_list *env_lst)
{
	char	*str0;
	char	*tmp;
	char	*cacommenceafairebeaucoup;
	char	*ntm;
	char	quote;
	int		i;
	int		start;
	int		encorestart;

	quote = 0;
	start = 0;
	str0 = line;
	i = 0;
	tmp = NULL;
	while (*line)
	{
		if ((*line == '\'' || *line == '"') && !quote)
		{
			start = i + 1;
			quote = *line;
			line++;
			i++;
		}
		if (!quote && *line)
		{
			
		}
		if (*line == quote) 
		{
			if (tmp)
			{
				cacommenceafairebeaucoup = wati_substr(str0, start, i - start);
				if (quote == '"')
				{
					ntm = modify_token(cacommenceafairebeaucoup, env_lst);
					free(cacommenceafairebeaucoup);
					cacommenceafairebeaucoup = ntm;
				}
				tmp = wati_strjoin(tmp, cacommenceafairebeaucoup);
				free(cacommenceafairebeaucoup);
			}
			else
				tmp = wati_substr(str0, start, i - start);
			wati_printf("word without quote = %s\n", tmp);
			quote = 0;
			start = i - 1;
		}
		line++;	
		i++;
	}
	if (tmp)
		free(tmp);
	wati_printf("Token = %s\n", line);
	return (str0);
}

// modify_token(line, env_lst) renvoie la ligne en changeant les dollars par la variable d'environnement

