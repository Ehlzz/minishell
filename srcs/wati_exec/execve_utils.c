/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:05:18 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/19 18:12:20 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *path)
{
	if (!wati_strncmp(path, "echo", wati_strlen(path)) \
			&& wati_strlen(path) == 4)
		return (ECHO);
	if (!wati_strncmp(path, "cd", wati_strlen(path)) \
			&& wati_strlen(path) == 2)
		return (CD);
	if (!wati_strncmp(path, "pwd", wati_strlen(path)) \
			&& wati_strlen(path) == 3)
		return (PWD);
	if (!wati_strncmp(path, "export", wati_strlen(path)) \
			&& wati_strlen(path) == 6)
		return (EXPORT);
	if (!wati_strncmp(path, "unset", wati_strlen(path)) \
			&& wati_strlen(path) == 5)
		return (UNSET);
	if (!wati_strncmp(path, "env", wati_strlen(path)) \
			&& wati_strlen(path) == 3)
		return (ENV);
	if (!wati_strncmp(path, "exit", wati_strlen(path)) \
			&& wati_strlen(path) == 4)
		return (EXIT);
	return (0);
}

t_bool	exec_builtin(t_exec exec, t_list *env)
{
	int	id;

	id = is_builtin(*exec.strs);
	g_err = 0;
	if (id == ECHO)
		wati_echo(exec.strs);
	else if (id == PWD)
		print_pwd();
	else if (id == ENV)
		env_print(env);
	else if (id == EXPORT)
		export(env, exec.strs);
	return (TRUE);
}

static void	_env_delete(t_list **env, t_string *argv)
{
	argv++;
	while (*argv)
	{
		env_delete(env, *argv);
		argv++;
	}
}

t_bool	_execve(char **argv, t_pipe *fd, t_list **pids, t_shell *shell)
{
	int	id;

	id = is_builtin(*argv);
	if (id == CD)
		wati_chdir(&shell->env, *(argv + 1));
	else if (id == UNSET)
		_env_delete(&shell->env, argv);
	else if (id == EXPORT && *(argv + 1))
		export(shell->env, argv);
	else if (id == EXIT)
	{
		close_spipe(*fd);
		if (*pids)
			wati_lstclear(pids, free);
		ft_exit(shell, argv);
	}
	else
		return (FALSE);
	return (TRUE);
}

void	__execve(t_exec exec, t_list *env)
{
	char	**envp;

	envp = wati_lstsplit(env);
	execve(exec.path, exec.strs, envp);
}
