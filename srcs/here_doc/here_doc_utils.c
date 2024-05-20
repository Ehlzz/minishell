/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:59:28 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 18:07:48 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_line(int verif_quote, t_list *env, t_heredoc *heredoc)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line || g_err == 130)
		return (NULL);
	if (!wati_strncmp(heredoc->limiter, line, wati_strlen(heredoc->limiter)) && \
		wati_strlen(line) == wati_strlen(heredoc->limiter))
		return (NULL);
	if (*line == '\0')
		return (line);
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

void	free_in_fork(t_cmd *cmd, t_list **list, t_shell *shell)
{
	btree_clear(shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	free_cmd(cmd);
	wati_lstiter(*list, free_token);
	wati_lstclear(&shell->list, free);
}

void	close_free_utils(t_heredoc *heredoc, char *line, int fd)
{
	free(heredoc->file);
	free(heredoc->limiter);
	free(line);
	wati_close(fd);
}
