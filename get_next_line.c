/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:50:03 by blohrer           #+#    #+#             */
/*   Updated: 2024/11/21 12:38:52 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	temp = ft_strdup(&(*buffer)[i + ((*buffer)[i] == '\n')]);
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		tmp[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			tmp[bytes_read] = '\0';
			buffer = ft_strjoin(buffer, tmp);
		}
	}
	if (bytes_read < 0 || !buffer || !*buffer)
		return (free(buffer), buffer = NULL, NULL);
	return (extract_line(&buffer));
}

// char	*get_next_line(int fd)
// {
// 	static char	*buffer;
// 	char		tmp[BUFFER_SIZE + 1];
// 	int			bytes_read;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (!ft_strchr(buffer, '\n'))
// 	{
// 		bytes_read = read(fd, tmp, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 			break ;
// 		tmp[bytes_read] = '\0';
// 		buffer = ft_strjoin(buffer, tmp);
// 	}
// 	if (!buffer || !*buffer)
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 		return (NULL);
// 	}
// 	return (extract_line(&buffer));
// }
