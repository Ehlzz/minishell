/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:21:56 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/22 12:51:09 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_number(char *str)
{
	while (str && *str && wati_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (str && *str)
	{
		if (!wati_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_overflow(char *str)
{
	if (!is_number(str))
		return (1);
	while (str && *str && wati_isspace(*str))
		str++;
	if (*str != '-' && wati_strlen(str) > 19)
		return (1);
	if (*str == '-' && wati_strlen(str) > 20)
		return (1);
	if (wati_strlen(str) == 19 && \
		wati_strncmp(str, "9223372036854775807", 19) > 0)
		return (1);
	if (wati_strlen(str) == 20 && \
		wati_strncmp(str, "-9223372036854775808", 20) > 0)
		return (1);
	return (0);
}

void	ft_free_before_exit(t_shell *shell, char **argv)
{
	wati_free_tab(argv);
	btree_clear(&shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	wati_lstclear(&shell->list, free);
}

void	ft_exit(t_shell *shell, char **strs)
{
	int	status;

	if (!strs[1])
	{
		ft_free_before_exit(shell, strs);
		wati_putendl_fd("exit", 2);
		exit(g_err);
	}
	if (check_overflow(strs[1]))
	{
		wati_putstr_fd("exit\nminishell: exit: ", 2);
		wati_putstr_fd(strs[1], 2);
		wati_putstr_fd(": numeric argument required\n", 2);
		ft_free_before_exit(shell, strs);
		exit(2);
	}
	if (is_number(strs[1]) && strs[2])
	{
		g_err = 1;
		return (wati_putstr_fd("minishell: exit: too many arguments\n", 2));
	}
	status = wati_atoll(strs[1]);
	ft_free_before_exit(shell, strs);
	wati_putendl_fd("exit", 2);
	exit(status % 256);
}
