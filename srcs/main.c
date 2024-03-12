/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/12 14:06:22 by ehalliez         ###   ########.fr       */
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

int	clean_lst(t_list *lst)
{
	wati_lstiter(lst, print);
	wati_lstiter(lst, free);
	wati_lstclean(&lst);
	return (0);
}

t_list	*init_parsing(char *line)
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
		if (!token)
			break;
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	free(str);
	if (test.quote)
	{
		clean_lst(lst);
		wati_putstr_fd("error: quote (test)\n", 2);
		return (NULL);
	}
	return (lst);
}

int	main(void)
{
	char	*str;
	t_list	*lst;

	str = readline("Minish$ ");
	lst = init_parsing(str);
	if (!lst)
		return (1);
	clean_lst(lst);
	return (0);
}
