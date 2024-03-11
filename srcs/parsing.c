/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:31:18 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 17:03:18 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*is_operator(char **ptr)
{
	char	*str0;
	char	*str;
	size_t	len;

	str0 = *ptr;
	if (is_operator_char(*str0))
	{
		str = str0;
		while (*str == *str0)
			str++;
		len = str - str0;
		*ptr += len;
		return (wati_substr(str0, 0, len));
	}
	return (NULL);
}

static char	*skip_space(char *str0)
{
	char	*str;

	str = str0;
	while (*str == ' ' && *str)
		str++;
	return (str);
}

static char	*get_next_word(char **ptr)
{
	char	*word;

	word = is_operator(ptr);
	if (!word)
		word = quote_manager(ptr);
	if (!word)
		return (NULL);
	*ptr = skip_space(*ptr);
	return (word);
}

t_list	*parsing(char *str)
{
	t_list	*list;

	list = NULL;
	while (*str)
		wati_lstadd_back(&list, wati_lstnew(get_next_word(&str)));
	return (list);
}
