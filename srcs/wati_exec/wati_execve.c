/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 21:04:16 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

int	is_star(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

void	__convert_strs(char *str, t_list *result)
{
	t_list	*wildcard;

	wildcard = wildcard_search(str);
	while (wildcard)
	{
		wati_lstadd_back(&result, wati_lstnew(wati_strdup(wildcard->content)));
		wildcard = wildcard->next;
	}
	wati_lstclear(&wildcard, free);
}

t_list	*convert_strs(t_list *strs, t_list *env)
{
	t_list	*result;
	char	*str;

	result = NULL;
	while (strs)
	{
		str = (char *)strs->content;
		if (is_star(str))
		{
			__convert_strs(str, result);
			strs = strs->next;
			continue ;
		}
		wati_lstadd_back(&result, \
		wati_lstnew(wati_strdup(verify_token(str, env))));
		strs = strs->next;
	}
	return (result);
}

pid_t	wati_execve(t_cmd *cmd, t_pipe *fd, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	pid = fork();
	if (!pid)
	{
		exec.path = get_path(cmd->strs->content, shell->env);
		cmd->strs = convert_strs(cmd->strs, shell->env);
		exec.strs = wati_lstsplit(cmd->strs);
		exec.envp = wati_lstsplit(shell->env);
		wati_dup2(cmd->fds, fd);
		close_fds(cmd->fds);
		close_spipe(*fd);
		if (exec.path && exec.envp)
			execve(exec.path, exec.strs, exec.envp);
		free(exec.path);
		free(exec.strs);
		free(exec.envp);
		btree_clear(shell->root, free_cmd);
		wati_lstclear(&shell->env, free);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
