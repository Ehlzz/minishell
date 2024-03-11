/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 21:46:36 by ehalliez         ###   ########.fr       */
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

char	*get_word(char **line)
{
	char	*str0;
	char	*str;
	char	quote_c;
	bool	quote;
	size_t	len;

	str = *line;
	str0 = str;
	quote = false;
	while (*str && *str != ' ' && !is_char_operator(*str))
	{
		if (*str == '"' || *str == 39)
		{
			quote_c = *str;
			quote = !quote;
		}
		str++;
	}
	while (quote && *str)
	{
		if (*str == quote_c)
		{
			str++;
			break ;
		}
		str++;
	}
	len = str - str0;
	*line += len;
	return (wati_substr(str0, 0, len));
	
}

char	*get_next_token(char **str)
{
	char	*token;
	
	token = get_operator(str);
	if (!token)
		token = get_word(str);
	if (!token)
		return (NULL);
	skip_space(str);
	return (token);
}	

int	main(int argc, char **argv)
{
	char	*str;
	char	*str0;
	t_list *lst;
	
	(void)argc;
	lst = NULL;
	str = ft_join_args(argv);
	str0 = str;
	while (*str)
		wati_lstadd_back(&lst, wati_lstnew(get_next_token(&str)));
	wati_lstiter(lst, print);
	wati_lstiter(lst, free);
	wati_lstclean(&lst);
	free(str0);
	return (0);
}
