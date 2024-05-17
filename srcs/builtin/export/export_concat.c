/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:42:36 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/15 18:22:24 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	strlen_to_char(char *str, int c)
{
	int	i;

	i = 0;
	while (*str++ && *str != c)
		i++;
	if (*str == c)
		i++;
	return (i);
}

int	is_char_before_char(char *str, int find, int until)
{
	while (*str)
	{
		if (*str == find)
			return (1);
		if (*str == until)
			return (0);
		str++;
	}
	return (0);
}

void	__export_concat(t_list *env, char *name, char *str)
{
	size_t	len;
	char	*tmp;
	char	*to_concat;

	len = wati_strlen_set(str, '+');
	to_concat = wati_strjoin(name, "=");
	free(name);
	name = wati_substr(str, len + 2, wati_strlen(str) - len - 2);
	tmp = wati_strjoin(to_concat, name);
	free(to_concat);
	free(name);
	env_add(&env, tmp);
}

void	export_concat(t_list *env, char *str)
{
	size_t	len;
	char	*tmp;
	char	*to_concat;
	t_list	*name;

	len = wati_strlen_set(str, '+');
	tmp = wati_substr(str, 0, len);
	name = get_var(env, tmp);
	if (!name)
		return (__export_concat(env, tmp, str));
	free(tmp);
	tmp = wati_substr(str, len + 2, wati_strlen(str) - len - 2);
	to_concat = verify_token(tmp, env);
	tmp = wati_strjoin(name->content, to_concat);
	free(to_concat);
	env_add(&env, tmp);
}

int	verif_identifier(char *str)
{
	if (!wati_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '+' && *str != '=')
	{
		if (!wati_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (*str == '+')
	{
		if (*(str + 1) != '=')
			return (0);
	}
	return (1);
}
