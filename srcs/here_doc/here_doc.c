/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:54:25 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/18 16:45:39 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/wait.h>
#include <signal.h>
#include "fcntl.h"

void	close_free_utils(t_heredoc *heredoc, char *line, int fd);
void	free_in_fork(t_cmd *cmd, t_list **list, t_shell *shell);
char	*get_line(int verif_quote, t_list *env);

int	is_quoted(char *str)
{
	int	verif;
	int	quote;

	quote = 0;
	verif = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && !quote)
		{
			quote = *str;
			str++;
		}
		if (*str == quote && quote)
		{
			verif = 1;
			quote = 0;
		}
		str++;
	}
	return (verif);
}

char	*random_filename(void)
{
	char	*tmp;
	char	*name;
	int		fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	name = malloc(17);
	if (!name)
		return (NULL);
	read(fd, name, 16);
	name[16] = 0;
	i = 0;
	while (i < 16)
	{
		name[i] = name[i] % 26 + 'a';
		i++;
	}
	tmp = wati_strjoin("/tmp/", name);
	free(name);
	close(fd);
	return (tmp);
}

void	__here_doc(t_heredoc *heredoc, t_cmd *cmd, \
t_list **list, t_shell *shell)
{
	char	*line;
	int		size_limiter;
	int		size_line;
	int		verif_quote;
	int		fd;

	fd = open(heredoc->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	verif_quote = is_quoted(heredoc->limiter);
	if (verif_quote)
		heredoc->limiter = remove_quote(heredoc->limiter);
	size_limiter = wati_strlen(heredoc->limiter);
	while (1)
	{
		line = get_line(verif_quote, shell->env);
		if (!line)
			break ;
		size_line = wati_strlen(line);
		if (!wati_strncmp(heredoc->limiter, line, size_limiter) && \
				size_line - 1 == size_limiter)
			break ;
		write(fd, line, size_line);
		free(line);
	}
	free_in_fork(cmd, list, shell);
	close_free_utils(heredoc, line, fd);
}

int	here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_fd		fd;
	int			r;
	pid_t		pid;
	t_heredoc	here_doc;

	r = 0;
	set_signal_ign();
	here_doc.file = random_filename();
	here_doc.limiter = limiter;
	pid = fork();
	if (!pid)
	{
		g_err = 0;
		set_signal_here_doc();
		__here_doc(&here_doc, cmd, list, shell);
		exit(g_err);
	}
	waitpid(pid, &g_err, 0);
	if (WEXITSTATUS(r))
		g_err = WEXITSTATUS(r);
	free(here_doc.limiter);
	fd = open(here_doc.file, O_RDONLY);
	unlink(here_doc.file);
	free(here_doc.file);
	return (fd);
}
