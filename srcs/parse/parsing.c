/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/19 18:17:08 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_operator(char **line)
{
	char	*str0;
	char	*str;
	int		len;

	str = *line;
	if (!is_char_operator(*str))
		return (NULL);
	str0 = str;
	while (*str == *str0)
		str++;
	len = str - str0;
	*line += len;
	return (wati_substr(str0, 0, len));
}

char	*skip_space(char **line)
{
	char	*str0;
	char	*str;
	size_t	len;

	str0 = *line;
	str = str0;
	while (*str && *str == ' ')
		str++;
	len = str - str0;
	*line += len;
	return (str0);
}

char	*get_word(char **line, t_test *test)
{
	char	*str0;
	char	*str;
	char	quote_c;

	str = *line;
	str0 = str;
	quote_c = 0;
	while (*str && !is_char_operator(*str))
	{
		if ((*str == '"' || *str == 39) && !quote_c)
		{
			quote_c = *str;
			test->quote = !test->quote;
		}
		else if (quote_c && *str == quote_c)
			test->quote = !test->quote;
		else if (quote_c && *str == ' ' && !test->quote)
			break ;
		else if (!quote_c && *str == ' ')
			break ;
		str++;
	}
	*line += str - str0;
	return (wati_substr(str0, 0, str - str0));
}

// char	*get_word(char **line, t_test *test)
// {
// 	char	*str0;
// 	char	*str;
// 	char	quote_c;
// 	size_t	len;

// 	str = *line;
// 	str0 = str;
// 	while (*str && *str != ' ' && !is_char_operator(*str))
// 	{
// 		if (*str == '"' || *str == 39)
// 		{
// 			quote_c = *str;
// 			test->quote = !test->quote;
// 		}
// 		str++;
// 	}
// 	while (*str)
// 	{
// 		if (*str == quote_c)
// 			test->quote = !test->quote;
// 		else if (*str == ' ' && !test->quote)
// 			break;
// 		str++;
// 	}
// 	len = str - str0;
// 	*line += len;
// 	return (wati_substr(str0, 0, len));
// }

char	*get_next_token(char **line, t_test *test)
{
	char	*token;

	token = get_operator(line);
	if (!token)
		token = get_word(line, test);
	if (test->quote)
		return (NULL);
	if (!token)
		return (NULL);
	skip_space(line);
	return (token);
}

int		is_dollar_operator(char *line)
{
	while (*line)
	{
		if (*line == '$')
			return (1);
		line++;
	}
	return (0);
}

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
	while (*str)
	{
		if (*str == ' ' || *str == '$')
			break ;
		str++;
	}
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
		if (*str == ' ' || *str == '$' 	)
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

// boucle infini si la variable d'environnement n'existe pas 201

char	*modify_token(char *line, t_list *env_lst)
{
	char	*start;
	char	*variable;
	char	*end;
	char	*tmp;

	while (is_dollar_operator(line))
	{
		start = start_to_dollar(line);
		if (*line == '"')
			variable = find_environment_variable(env_lst, dollar_to_dollar(line));
		else
			variable = find_environment_variable(env_lst, line);
		tmp = wati_strjoin(start, variable);
		start = tmp;
		end = dollar_to_end(line);
		tmp = wati_strjoin(tmp, end);
		free(start);
		line = tmp;
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

t_list	*init_parsing(char *line, t_list *env_lst)
{
	char	*token;
	char	*str;
	t_list	*lst;
	t_test	test;

	lst = NULL;
	test.quote = false;
	str = line;
	while (*line)
	{
		token = get_next_token(&line, &test);
		token = verify_token(token, env_lst);
		wati_printf("line = %s\n", token);
		if (!token)
			break ;
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	free(str);
	if (test.quote)
	{
		wati_lstclean(&lst);
		wati_putstr_fd("error: quote (test)\n", 2);
		return (NULL);
	}
	return (lst);
}
