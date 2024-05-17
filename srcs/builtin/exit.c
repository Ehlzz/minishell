/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:21:56 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 18:04:20 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_number(char **str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	str++;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!wati_isdigit(str[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_free_before_exit(t_shell *shell, char **argv)
{
	wati_free_tab(argv);
	btree_clear(shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	wati_lstclear(&shell->list, free);
}

void	ft_exit(t_shell *shell, char **strs)
{
	int	status;

	if (!strs[1])
	{
		ft_free_before_exit(shell, strs);
		exit(0);
	}
	if (is_number(strs) && strs[2])
		return (wati_putstr_fd("minishell: exit: too many arguments\n", 2));
	if (!is_number(strs) || (strs[1] && wati_strlen(strs[1]) > 19))
	{
		wati_putstr_fd("minishell: exit: ", 2);
		wati_putstr_fd(strs[1], 2);
		wati_putstr_fd(": numeric argument required\n", 2);
		ft_free_before_exit(shell, strs);
		exit(2);
	}
	status = wati_atoll(strs[1]);
	ft_free_before_exit(shell, strs);
	exit(status % 256);
}
