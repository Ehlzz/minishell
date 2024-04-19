/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:03:52 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/19 17:26:13 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;
	int			i;

	i = -1;
	if (fd == -1)
	{
		while (++i < 1024)
			free(stash[i]);
		return (NULL);
	}
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	stash[fd] = wati_read_nl(fd, stash[fd]);
	if (!*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = wati_save_line(stash[fd]);
	stash[fd] = wati_delete_line(stash[fd]);
	return (line);
}

char	*wati_read_nl(int fd, char *str)
{
	char	*tmp;
	char	*stash;
	char	*buf;
	int		bufsize;

	buf = malloc(BUFFER_SIZE + 1);
	if (!str)
		stash = wati_strdup("");
	else
		stash = wati_strdup(str);
	if (!buf)
		return (free_and_null(buf, str, stash));
	while (!check_newline(stash))
	{
		bufsize = read(fd, buf, BUFFER_SIZE);
		if (bufsize < 1)
			return (free_and_null(buf, str, stash));
		buf[bufsize] = 0;
		tmp = wati_strjoin(stash, buf);
		free(stash);
		stash = tmp;
	}
	free_and_null(buf, str, NULL);
	return (stash);
}

char	*wati_save_line(char *stash)
{
	int		i;
	int		size_to_nl;
	char	*result;

	i = 0;
	size_to_nl = wati_strlen_to_nl(stash);
	result = malloc(size_to_nl + 2);
	result[size_to_nl] = 0;
	while (stash && stash[i] != '\n' && stash[i])
	{
		result[i] = stash[i];
		i++;
	}
	if (stash && stash[i] == '\n')
		result[i] = '\n';
	result[i + 1] = 0;
	return (result);
}

char	*wati_delete_line(char *str)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	result = wati_strdup(&str[i]);
	if (!result)
		return (NULL);
	free_and_null(str, NULL, NULL);
	return (result);
}

char	*free_and_null(char *s1, char *s2, char *s3)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	if (!s3)
		return (NULL);
	return (s3);
}
