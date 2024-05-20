/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:18:25 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 21:23:45 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_quoted(char *str);

static int	is_variable(char *str)
{
	if (*str != '$')
		return (0);
	str++;
	while (*str)
	{
		if (!wati_isalpha(*str) && *str != '_' && *str != '?')
			return (0);
		if (*str == '?')
			break ;
		str++;
	}
	if (*str == '?' && *str + 1)
		return (0);
	return (1);
}

static char	**split_variable(char *str, t_list *env)
{
	char	**splitted;

	str = find_variable(env, str);
	if (!str)
		return (NULL);
	splitted = wati_split(str, ' ');
	free(str);
	return (splitted);
}

void	__convert_strs(char *str, t_list **result)
{
	t_list	*lst0;
	t_list	*wildcard;

	wildcard = wildcard_search(str);
	lst0 = wildcard;
	while (wildcard)
	{
		wati_lstadd_back(result, wati_lstnew(wati_strdup(wildcard->content)));
		wildcard = wildcard->next;
	}
	wati_lstclear(&lst0, free);
}

void	_convert_strs(t_list **result, t_list *env, char *str)
{
	int		i;
	char	**splitted;

	i = 0;
	if (is_variable(str))
	{
		splitted = split_variable(str, env);
		if (!splitted[i])
			wati_lstadd_back(result, \
			wati_lstnew(wati_strdup("")));
		while (splitted[i])
		{
			wati_lstadd_back(result, \
			wati_lstnew(wati_strdup(splitted[i])));
			i++;
		}
		wati_free_tab(splitted);
	}
	else
		wati_lstadd_back(result, \
		wati_lstnew(verify_token(wati_strdup(str), env)));
}

t_list	*convert_strs(t_list *strs, t_list *env)
{
	t_list	*result;
	char	*str;

	result = NULL;
	while (strs)
	{
		str = (char *)strs->content;
		if (is_star(str) && !is_quoted(str))
		{
			__convert_strs(str, &result);
			strs = strs->next;
			continue ;
		}
		_convert_strs(&result, env, str);
		strs = strs->next;
	}
	return (result);
}
