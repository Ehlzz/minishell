/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:40:47 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 22:41:25 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_operator(char c)
{
	return (c == '|' || c == '&'
		|| c == '<' || c == '>'
		|| c == '(' || c == ')');
}

void	print(void *str)
{
	wati_putendl_fd(str, 1);
}

int	count_dollars(char *line)
{
	int		quote;
	int		count;

	count = 0;
	quote = 0;
	while (*line)
	{
		if ((*line == '\'' || *line == '"') && !quote)
		{
			quote = *line;
			line++;
		}
		if (*line == quote)
			quote = 0;
		if (*line == '$' && quote != '\'')
			count++;
		line++;
	}
	return (count);
}
