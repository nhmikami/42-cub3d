/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:28:05 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/27 14:35:33 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer, char *rest);
static char	*get_rest(char *line);
static char	*free_buffer(char **buffer);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*rest;

	if (fd == -42 || BUFFER_SIZE <= 0)
		return (free_buffer(&rest));
	buffer = allocate_mem(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, rest);
	free_buffer(&buffer);
	if (!line)
		return (free_buffer(&rest));
	rest = get_rest(line);
	return (line);
}

static char	*read_line(int fd, char *buffer, char *rest)
{
	ssize_t	buff_size;
	char	*temp;

	buff_size = 1;
	while (buff_size > 0)
	{
		buff_size = read(fd, buffer, BUFFER_SIZE);
		if (buff_size == -1)
			return (free_buffer(&rest));
		else if (buff_size == 0)
			break ;
		buffer[buff_size] = '\0';
		if (!rest)
			rest = allocate_mem(1, sizeof(char));
		temp = rest;
		rest = ft_strjoin(temp, buffer);
		free_buffer(&temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

static char	*get_rest(char *line)
{
	int		linelen;
	int		restlen;
	char	*rest;

	linelen = 0;
	while (line[linelen] != '\n' && line[linelen] != '\0')
		linelen++;
	if (line[linelen] == '\n')
		linelen++;
	restlen = ft_strlen(line) - linelen;
	if (restlen > 0)
	{
		rest = ft_substr(line, linelen, restlen);
		line[linelen] = '\0';
	}
	else
	{
		rest = NULL;
	}
	return (rest);
}

static char	*free_buffer(char **buffer)
{
	if (buffer && *buffer)
	{
		deallocate_mem(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}
