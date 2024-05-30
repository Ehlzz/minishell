/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:59:28 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/30 10:52:54 by bedarenn         ###   ########.fr       */
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
