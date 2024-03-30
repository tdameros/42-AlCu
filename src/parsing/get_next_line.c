/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:17:46 by tdameros          #+#    #+#             */
/*   Updated: 2022/11/23 00:34:49 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "parsing/get_next_line.h"

/**
 * Consumable function that returns a line on each call.
 * Read the file descriptor with BUFFER_SIZE macro (defined at 42 by default).
 * Support multiple file descriptors (OPEN_MAX macro).
 * @param fd
 * @return char * line allocate with malloc
 */
char	*get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE];
	char		*line;
	char		*line_temp;
	int			is_line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (is_empty_buf(buf[fd], BUFFER_SIZE)
		&& read(fd, buf[fd], BUFFER_SIZE) <= 0)
		return (NULL);
	line = extract_line_in_buf(buf[fd], BUFFER_SIZE, &is_line);
	if (line == NULL)
		return (NULL);
	while (is_line == 0)
	{
		if (read(fd, buf[fd], BUFFER_SIZE) <= 0)
			return (line);
		line_temp = extract_line_in_buf(buf[fd], BUFFER_SIZE, &is_line);
		if (line_temp == NULL)
			return (free_ret_null(line, NULL));
		line = strjoin_free(line, line_temp);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

/**
 * @param buf
 * @param buf_size
 * @return boolean value is the buffer is empty
 */
int	is_empty_buf(char *buf, size_t buf_size)
{
	size_t	index;

	index = 0;
	while (index < buf_size)
	{
		if (buf[index] != '\0')
			return (0);
		index++;
	}
	return (1);
}

/**
 * Extract a line and replace line by 0 in the buffer.
 * Set the variable is_line to 1 if it ends with '\n'.
 * @param buf
 * @param buf_size
 * @param is_line boolean value if the line ends with '\n
 * @return char * line allocate with malloc
 */
char	*extract_line_in_buf(char *buf, size_t buf_size, int *is_line)
{
	char	*line;
	size_t	start;
	size_t	len;

	start = start_line_in_buf(buf, buf_size);
	len = len_line_in_buf(buf, buf_size, start);
	line = sub_line_in_buf(buf, start, len);
	if (line == NULL)
		return (NULL);
	*is_line = line[len - 1] == '\n';
	return (line);
}

/**
 * Try to free 2 void pointer and return NULL.
 * @param ptr1 pointer allocate with malloc
 * @param ptr2 pointer allocate with malloc
 * @return NULL
 */
char	*free_ret_null(void *ptr1, void *ptr2)
{
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
	return (NULL);
}