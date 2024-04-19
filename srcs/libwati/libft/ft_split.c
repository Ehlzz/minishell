/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:07:04 by ehalliez          #+#    #+#             */
/*   Updated: 2023/12/19 16:59:30 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		words++;
	while (str[i])
	{
		if (str[i] == c && (str[i + 1] != c && str[i + 1] != '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	w_l(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*copy_into(char *s, int i, char c)
{
	char	*result;
	int		j;
	int		len;

	j = 0;
	len = w_l((char *)s, c, i);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

static	void	split_strings(const char *s, char c, char **result)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (s[i + 1] != c && s[i + 1] != '\0')
	{
		result[j] = copy_into((char *)s, i + 1, c);
		j++;
	}
	while (s[++i])
	{
		if (s[i] == c && (s[i + 1] != c) && s[i + 1] != '\0')
		{
			result[j] = copy_into((char *)s, i + 1, c);
			j++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!result)
		return (0);
	result[count_words((char *)s, c)] = 0;
	split_strings(s, c, result);
	return (result);
}
