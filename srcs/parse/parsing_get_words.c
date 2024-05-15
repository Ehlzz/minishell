/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:31:32 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/15 13:59:21 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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

char	*get_line(int verif_quote, t_list *env)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line)
		return (NULL);
	if (!verif_quote)
	{
		tmp = line;
		line = verify_token(tmp, env);
		tmp = line;
		line = wati_strjoin(line, "\n");
		free(tmp);
		return (line);
	}
	tmp = line;
	line = wati_strjoin(line, "\n");
	free(tmp);
	return (line);	
}

int __here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell)
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
	btree_clear(shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	free_cmd(cmd);
	wati_lstiter(*list, free_token);
	wati_lstclear(&shell->list, free);
	free(line);
	free(limiter);
	close (fd);
	exit(EXIT_SUCCESS);
}

int	here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_fd	fd;
	int		r;
	pid_t	pid;

	r = 0;
	pid = fork();
	if (!pid)
		__here_doc(limiter, cmd, list, shell);
	else
		waitpid(pid, &r, 0);
	error_code = r;
	free(limiter);
	fd = open("/tmp/output", O_RDONLY);
	unlink("/tmp/output");
	return (fd);
}

// int main(int argc, char **argv)
// {
// 	if (argc != 1)
// 		here_doc(argv[1]);
// }
