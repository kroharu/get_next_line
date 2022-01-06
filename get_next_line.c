/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:57:50 by ladrian           #+#    #+#             */
/*   Updated: 2021/12/07 17:45:14 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *static_line)
{
	int		i;
	char	*temp;

	i = 0;
	if (!static_line[i])
		return (NULL);
	while (static_line[i] && static_line[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (static_line[i] && static_line[i] != '\n')
	{
		temp[i] = static_line[i];
		i++;
	}
	if (static_line[i] == '\n')
	{
		temp[i] = static_line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_save_line(char *static_line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (static_line[i] && static_line[i] != '\n')
		i++;
	if (!static_line[i])
	{
		free(static_line);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen(static_line) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (static_line[i])
		temp[j++] = static_line[i++];
	temp[j] = '\0';
	free(static_line);
	return (temp);
}

char	*ft_read_line_and_save(int fd, char *static_line)
{
	char	*buf;
	int		read_bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(static_line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		static_line = ft_strjoin(static_line, buf);
	}
	free(buf);
	return (static_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	static_line = ft_read_line_and_save(fd, static_line);
	if (!static_line)
		return (NULL);
	line = ft_get_line(static_line);
	static_line = ft_save_line(static_line);
	return (line);
}
