/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:31:32 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/15 12:27:37 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
extern int error_code;

char	*get_operator_line(char **line)
{
	char	*str0;
	char	*str;
	int		len;

	str = *line;
	if (!is_char_operator(*str))
		return (NULL);
	str0 = str;
	while (*str == *str0)
		str++;
	len = str - str0;
	*line += len;
	return (wati_substr(str0, 0, len));
}

char	*skip_space(char **line)
{
	char	*str0;
	char	*str;
	size_t	len;

	str0 = *line;
	str = str0;
	while (*str && *str == ' ')
		str++;
	len = str - str0;
	*line += len;
	return (str0);
}

char	*get_word(char **line, t_test *test)
{
	char	*str0;
	char	*str;
	char	quote_c;

	str = *line;
	str0 = str;
	quote_c = 0;
	while (*str)
	{
		if ((*str == '"' || *str == 39) && !quote_c)
		{
			quote_c = *str;
			test->quote = !test->quote;
		}
		else if (quote_c && *str == quote_c)
		{
			quote_c = 0;
			test->quote = !test->quote;
		}
		else if (is_char_operator(*str) && !test->quote)
			break ;
		else if ((!quote_c || (quote_c && !test->quote)) && *str == ' ')
			break ;
		str++;
	}
	*line += str - str0;
	return (wati_substr(str0, 0, str - str0));
}

char	*get_next_token(char **line, t_test *test)
{
	char	*token;

	token = get_operator_line(line);
	if (!token)
		token = get_word(line, test);
	if (test->quote)
	{
		free(token);
		return (NULL);
	}
	if (!token)
		return (NULL);
	skip_space(line);
	return (token);
}

#include "fcntl.h"

int	is_quoted(char *str)
{	
	int	verif;
	int quote;

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

char	*get_line(int verif_quote)
{
	char	*line;
	char	*tmp;

	line = readline(0);
	if (!line)
		return (NULL);
	tmp = line;
	line = wati_strjoin(line, "\n");
	free(tmp);
	if (verif_quote)
	{
		tmp = line;
		line = verify_token(line)
	}
	return (line);	
}

int __here_doc(char *limiter, int fd)
{
	char	*line;
	int		size_limiter;
	int		size_line;
	int		verif_quote;

	verif_quote = is_quoted(limiter);
	size_limiter = wati_strlen(limiter);
	while (1)
	{
		wati_putstr_fd("> ", 1);
		line = get_line(verif_quote);
		if (!line)
			break;
		size_line = wati_strlen(line);
		if (!wati_strncmp(limiter, line, size_limiter) && \
				size_line - 1 == size_limiter)
			break ;
		write(fd, line, size_line);
		free(line);
	}
	free(line);
	free(limiter);
	close (fd);
	exit(EXIT_SUCCESS);
}

int	here_doc(char *limiter)
{
	int		fd;
	int		r;
	pid_t	pid;	

	fd = open("/tmp/output", O_RDWR | O_CREAT | O_TRUNC, 0644);
	r = 0;
	if (!fd)
		return (-1);
	pid = fork();
	if (!pid)
		__here_doc(limiter, fd);
	else
		waitpid(pid, &r, 0);
	error_code = r;
	free(limiter);
	return (fd);
}

// int main(int argc, char **argv)
// {
// 	if (argc != 1)
// 		here_doc(argv[1]);
// }
