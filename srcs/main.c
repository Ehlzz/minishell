/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 20:44:36 by ehalliez         ###   ########.fr       */
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

char	*is_operator(char **str)
{
	char	*str0;
	char	*str;
	int		len;
	if (is_char_operator(*str))
	{
		str0 = str;
		while (str == str0)
			len++;
	}
	return (NULL);
}

char	*get_next_word(char **str)
{
	char	*word
	
	word = is_operator(str);
	return (word);
}

int	main(int argc, char **argv)
{
	char	*str;
	t_list *lst;
	
	(void)argc;
	lst = NULL;
	str = ft_join_args(argv);
	while (*str)
		wati_lstadd_back(&lst, wati_lstnew(get_next_word(&str)));
	wati_lstiter(lst, print);
	free(str);
	return (0);
}
