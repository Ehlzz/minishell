/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:59:00 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/06 15:59:59 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrncmp(char *str1, char *str2, int n)
{
	int	str1_len;
	int	str2_len;

	str1_len = wati_strlen(str1) - 1;
	str2_len = wati_strlen(str2) - 1;
	while (str1_len + 1 && str2_len + 1 && n)
	{
		if (str1[str1_len] != str2[str2_len])
			return (str1[str1_len] - str2[str2_len]);
		str1_len--;
		str2_len--;
		n--;
	}
	return (0);
}

char	*get_next_star(char *pattern)
{
	int		len_start;
	int		len_end;
	char	*str;

	str = pattern;
	while (*str && *str != '*')
		str++;
	len_start = str - pattern + 1;
	str++;
	while (*str && *str != '*')
		str++;
	len_end = str - pattern;
	if (!*str)
		str--;
	return (wati_substr(pattern, len_start, len_end - len_start));
}

char	*get_pattern(char *content, char *search)
{
	char	*star_pattern;

	star_pattern = get_next_star(search - 1);
	content = wati_strnstr(content, star_pattern, wati_strlen(content));
	free(star_pattern);
	return (content);
}

int	wildcard_checker(char *search, char *content)
{
	while (*search || *content)
	{
		if (*search == '*')
		{
			while (*search == '*')
				search++;
			if (!*search)
				return (1);
			content = get_pattern(content, search);
		}
		if (!content || !*content || (*search++ != *content++))
			return (0);
	}
	return (1);
}
