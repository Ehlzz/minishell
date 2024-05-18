/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:40:47 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/18 14:57:29 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_operator(char c)
{
	return (c == '|' || c == '&'
		|| c == '<' || c == '>'
		|| c == '(' || c == ')');
}

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
			result = wati_strjoin(tmp, argv[i + 1]);
			free(tmp);
		}
		i++;
	}
	return (result);
}

void	print(void *str)
{
	wati_putendl_fd(str, 1);
}

int	is_dollar_operator(char *line)
{
	while (*line)
	{
		if (*line == '$')
			return (1);
		line++;
	}
	return (0);
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
