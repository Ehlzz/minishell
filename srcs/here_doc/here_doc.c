/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:54:25 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/17 12:08:43 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/wait.h>
#include <signal.h>
#include "fcntl.h"

void	close_free_utils(char *limiter, char *line, int fd);
void	free_in_fork(t_cmd *cmd, t_list **list, t_shell *shell);
char	*get_line(int verif_quote, t_list *env);
// void	set_signal_here_doc(void);

// void	sig_here_doc(int code)
// {
// 	if (code == SIGINT)
// 	{
// 		error_code = 130;
// 	}	
// 	else if (code == SIGQUIT)
// 	{
// 	}
// }

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

void	__here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell)
{
	char	*line;
	int		size_limiter;
	int		size_line;
	int		verif_quote;
	int		fd;

	fd = open("/tmp/output", O_RDWR | O_CREAT | O_TRUNC, 0644);
	verif_quote = is_quoted(limiter);
	if (verif_quote)
		limiter = remove_quote(limiter);
	size_limiter = wati_strlen(limiter);
	while (1)
	{
		line = get_line(verif_quote, shell->env);
		if (!line)
			break ;
		size_line = wati_strlen(line);
		if (!wati_strncmp(limiter, line, size_limiter) && \
				size_line - 1 == size_limiter)
			break ;
		write(fd, line, size_line);
		free(line);
	}
	free_in_fork(cmd, list, shell);
	close_free_utils(limiter, line, fd);
}

int	here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_fd	fd;
	int		r;
	pid_t	pid;

	r = 0;
	pid = fork();
	if (!pid)
	{
		//set_signal_here_doc();
		__here_doc(limiter, cmd, list, shell);
	}
	else
		waitpid(pid, &r, 0);
	error_code = r;
	free(limiter);
	fd = open("/tmp/output", O_RDONLY);
	unlink("/tmp/output");
	return (fd);
}
