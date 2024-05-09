/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:48:21 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/09 16:50:01 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*_add_quote(char *str, char *result, char *str0, int i)
{
	while (*str)
	{
		result[i] = *str;
		i++;
		str++;
	}
	result[i] = '"';
	result[i + 1] = 0;
	free(str0);
	return (result);
}

char	*add_quote(char *str)
{
	int		i;
	int		len;
	char	*str0;
	char	*result;

	i = 0;
	str0 = str;
	len = wati_strlen(str) + 2;
	result = malloc(len + 1);
	while (*str && *str != '=')
	{
		result[i] = *str;
		i++;
		str++;
	}
	result[i] = *str;
	i++;
	str++;
	result[i] = '"';
	i++;
	return (_add_quote(str, result, str0, i));
}
