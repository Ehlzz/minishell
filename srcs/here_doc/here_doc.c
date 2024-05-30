/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:54:25 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/30 10:53:12 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/wait.h>
#include <signal.h>
#include "fcntl.h"

int		wati_nothing(void);

char	*get_line(int verif_quote, t_list *env, t_heredoc *heredoc);

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
	wati_close(fd);
	return (tmp);
}

void	__here_doc(t_heredoc *heredoc, t_shell *shell)
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
		line = get_line(verif_quote, shell->env, heredoc);
		if (!line)
			break ;
		size_line = wati_strlen(line);
		write(fd, line, size_line);
		free(line);
	}
	close(fd);
}

int	here_doc(char *limiter, t_shell *shell)
{
	t_fd		fd;
	t_heredoc	here_doc;

	set_signal_ign();
	here_doc.file = random_filename();
	here_doc.limiter = limiter;
	g_err = 0;
	set_signal_here_doc();
	rl_event_hook = &wati_nothing;
	__here_doc(&here_doc, shell);
	free(here_doc.limiter);
	if (g_err != 0)
	{
		unlink(here_doc.file);
		free(here_doc.file);
		return (-1);
	}
	fd = open(here_doc.file, O_RDONLY);
	unlink(here_doc.file);
	free(here_doc.file);
	return (fd);
}
