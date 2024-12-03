/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:23:50 by blohrer           #+#    #+#             */
/*   Updated: 2024/12/03 10:33:01 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*allocate_and_copy(const char *str, size_t start)
{
	size_t	i;
	char	*rest;

	rest = (char *)malloc(sizeof(char) * (ft_strlen(str) - start + 1));
	if (!rest)
		return (NULL);
	i = 0;
	while (str[start])
		rest[i++] = str[start++];
	rest[i] = '\0';
	return (rest);
}

char	*save_remaining(char *str)
{
	size_t	i;
	char	*rest;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	rest = allocate_and_copy(str, i);
	free(str);
	return (rest);
}

char	*clean_up(char **rest)
{
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!rest[fd] || !ft_strchr(rest[fd], '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_up(&rest[fd]));
		buffer[bytes_read] = '\0';
		rest[fd] = ft_strjoin(rest[fd], buffer);
		if (!rest[fd])
			return (clean_up(&rest[fd]));
	}
	if (!rest[fd] || (bytes_read == 0 && rest[fd][0] == '\0'))
		return (clean_up(&rest[fd]));
	line = extract_line(rest[fd]);
	rest[fd] = save_remaining(rest[fd]);
	if (!line)
		return (clean_up(&rest[fd]));
	return (line);
}