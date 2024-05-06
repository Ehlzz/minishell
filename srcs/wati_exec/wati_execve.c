/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:54:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/06 22:52:03 by ehalliez         ###   ########.fr       */
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

int	is_builtin(char **strs)
{
	if (!wati_strncmp(*strs, "echo", wati_strlen(*strs)))
		return (ECHO);
	if (!wati_strncmp(*strs, "cd", wati_strlen(*strs)))
		return (CD);
	if (!wati_strncmp(*strs, "pwd", wati_strlen(*strs)))
		return (PWD);
	if (!wati_strncmp(*strs, "export", wati_strlen(*strs)))
		return (EXPORT);
	if (!wati_strncmp(*strs, "unset", wati_strlen(*strs)))
		return (UNSET);
	if (!wati_strncmp(*strs, "env", wati_strlen(*strs)))
		return (ENV);
	if (!wati_strncmp(*strs, "exit", wati_strlen(*strs)))
		return (EXIT);
	return (0);
}

void	exec_builtin(t_exec exec, int builtin, t_shell *shell)
{
	if (builtin == ECHO)
		return (wati_echo(exec.strs));
	if (builtin == CD)
		return (wati_chdir(&(shell->env), exec.strs[1]));
	if (builtin == PWD)
		return (print_pwd());
	if (builtin == EXPORT)
		return (export(shell->env, exec.strs));
	if (builtin == UNSET)
		return (env_delete(&(shell->env), exec.strs[1]));
	if (builtin == ENV)
		return (env_print(shell->env));
	if (builtin == EXIT)
		return ;
}

pid_t	wati_execve(t_cmd *cmd, t_pipe *fd, t_shell *shell)
{
	pid_t	pid;
	t_exec	exec;

	if (!cmd || !cmd->strs || !cmd->strs->content)
		return (0);
	exec.path = get_path(cmd->strs->content, shell->env);
	cmd->strs = convert_strs(cmd->strs, shell->env);
	exec.strs = wati_lstsplit(cmd->strs);
	exec.envp = wati_lstsplit(shell->env);
	if (is_builtin(exec.strs))
	{
		exec_builtin(exec, is_builtin(exec.strs), shell);
		printf("executed builtin\n");
		return (0);
	}
	pid = fork();
	if (!pid)
	{
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
