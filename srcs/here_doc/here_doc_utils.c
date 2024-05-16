/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:59:28 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/16 19:56:46 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_line(int verif_quote, t_list *env)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (*line == '\0')
		return (line);
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

void	free_in_fork(t_cmd *cmd, t_list **list, t_shell *shell)
{
	btree_clear(shell->root, free_cmd);
	wati_lstclear(&shell->env, free);
	free_cmd(cmd);
	wati_lstiter(*list, free_token);
	wati_lstclear(&shell->list, free);
}

void	close_free_utils(char *limiter, char *line, int fd)
{
	free(limiter);
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}
