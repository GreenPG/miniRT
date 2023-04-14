/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:44:24 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/16 10:55:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static char	*line_filling(char *buf, char *line)
{
	int				line_size;	
	int				i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line_size = ft_strlen(line) + i;
	line = ft_gnl_strjoin(line, buf, line_size);
	if (!line)
		return (NULL);
	return (line);
}

static int	read_file(int fd, char *buf, char **line)
{
	int				readed_bytes;

	if (buf[0] != '\0')
	{
		readed_bytes = 1;
		*line = line_filling(buf, *line);
	}	
	else
	{
		readed_bytes = read(fd, buf, BUFFER_SIZE);
		*line = line_filling(buf, *line);
	}
	return (readed_bytes);
}

static char	*clean_buffer(char *buf)
{
	int				i;
	int				buf_len;

	i = -1;
	buf_len = ft_strlen(buf);
	while (buf[++i])
	{
		if (buf[i] == '\n')
			break ;
	}
	if (i < buf_len && buf[i + 1] != '\0')
		clean_filled_buffer(buf, i);
	else
	{
		i = -1;
		while (buf[++i])
			buf[i] = '\0';
	}
	return (buf);
}

char	*boo_while(int fd, char **buf, char *line)
{
	int				boo;
	int				i;
	int				readed_bytes;

	readed_bytes = 1;
	boo = 0;
	while (boo == 0 && readed_bytes != 0)
	{
		readed_bytes = read_file(fd, buf[fd], &line);
		if (readed_bytes == -1 || (readed_bytes == 0 && line[0] == 0))
		{
			free(line);
			return (NULL);
		}
		if (buf[fd][0] != '\0')
			buf[fd] = clean_buffer(buf[fd]);
		i = -1;
		while (line[++i])
		{
			if (line[i] == '\n')
				boo++;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*buf[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf[fd])
	{
		buf[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf[fd])
			return (NULL);
	}
	line = ft_calloc(2, sizeof(char));
	if (!line)
	{
		free(buf[fd]);
		return (NULL);
	}
	line = boo_while(fd, buf, line);
	if (!line)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (line);
	}
	return (line);
}
