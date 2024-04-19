/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:20:58 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/19 21:32:22 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_quote(char *str)
{
	int		i;
	int		len;
	char	*str0;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	str0 = str;
	len = wati_strlen(str);
	result = malloc(len + 3);
	if (!result)
		return (NULL);
	while (*str && *str != '=')
	{
		result[i] = *str;
		str++;
		i++;
	}
	result[i] = 0;
	if (!*str)
	{
		wati_printf("%s\n", result);
		return (result);
	}
	result[i] = '=';
	if (*str == '"')
		str++;
	result[i + 1]= '"';
	i++;
	str++;
	while (*str)
	{
		i++;
		result[i] = *str;
		str++;
	}
	result[i + 1] = '"';
	result[i + 2] = 0;
	wati_printf("%s\n", result);
	return (result);
}

void	add_to_env(char *str, t_list **env)
{
	int	len;

	len = wati_strlen(str);
	add_quote(str);
	if (str && env)
		wati_lstadd_back(env, wati_lstnew(str));
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_list	*env;

	env = env_getlist(envp);
	set_readline_signal();
	(void)argc;
	while (1)
	{
		str = wati_readline(env, argv[0]);
		add_history(str);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(env, argv[0]);
		}
		if (str == NULL)
			break ;
		lst = init_parsing(str, env);
		add_to_env(lst->content, &env);
		wati_env(env);
		wati_lstiter(lst, print);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
