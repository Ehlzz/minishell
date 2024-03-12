/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/12 13:12:54 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libwati.h>

char	*ft_join_args(char **argv)
{
	char	*tmp;
	char	*result;
	int		i;
	
	i = 1;
	tmp = NULL;
	result = wati_strdup(argv[1]);
	while (argv[i])
	{
		if (argv[i + 1])
		{
			tmp = result;
			result = wati_strjoin(tmp, " ");
			free(tmp);
			tmp = result;
			result =  wati_strjoin(tmp, argv[i + 1]);
			free(tmp);
		}
		i++;
	}
	return (result);
}

void print(void *str)
{
	wati_putendl_fd(str, 1);
}

int is_char_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

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
	size_t	len;

	str = *line;
	str0 = str;
	while (*str && *str != ' ' && !is_char_operator(*str))
	{
		if (*str == '"' || *str == 39)
		{
			quote_c = *str;
			test->quote = !test->quote;
		}
		str++;
	}
	while (test->quote && *str)
	{
		if (*str == quote_c)
		{
			test->quote = !test->quote;
			str++;
			break ;
		}
		str++;
	}

	while (*str && *str != ' ')
	{
		if (*str == quote_c)
			test->quote = !test->quote;
		str++;
	}
	len = str - str0;
	*line += len;
	return (wati_substr(str0, 0, len));
	
}

char	*get_next_token(char **str, t_test *test)
{
	char	*token;
	
	token = get_operator(str);
	test->quote = false;
	if (!token)
		token = get_word(str, test);
	if (test->quote)
		return (NULL);
	if (!token)
		return (NULL);
	skip_space(str);
	return (token);
}	

int	main(void)
{
	char	*str;
	char	*str0;
	char	*token;
	t_list	*lst;
	t_test	test;
	
	lst = NULL;
	// str = ft_join_args(argv);
	str = readline("Minish$ ");
	str0 = str;
	while (*str)
	{
		token = get_next_token(&str, &test);
		if (!token)
			break;
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	wati_lstiter(lst, print);
	wati_lstiter(lst, free);
	wati_lstclean(&lst);
	if (test.quote)
		return (wati_putstr_fd("error: quote (test)\n", 2));
	free(str0);
	return (0);
}
