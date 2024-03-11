/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:59:55 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 17:25:08 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*quote_manager(char **ptr)
{
	char	*str0;
	char	*str;
	size_t	len;
	int		quote;

	str0 = *ptr;
	str = str0;
	quote = 0;
	while (*str != ' ' && !is_operator_char(*str) && *str)
		str++;
	len = str - str0;
	*ptr += len;
	return (wati_substr(str0, 0, len));
}
