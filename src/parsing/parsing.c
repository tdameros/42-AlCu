/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:26:23 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/29 23:26:24 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "game.h"
#include "parsing/get_next_line.h"

int	parse(t_game *game, int fd)
{
	char		*line;
	uint16_t	current;

	vector_init(&game->heaps, sizeof(uint16_t));
	line = get_next_line(fd);
	while (line != NULL)
	{
		current = parse_user_input(line, HEAP_MIN_ITEMS, HEAP_MAX_ITEMS);
		if (current == INVALID_USER_INPUT)
		{
			vector_free(&game->heaps);
			return (-1);
		}
		if (vector_add(&game->heaps, &current) != 0)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	if (errno != 0)
	{
		vector_free(&game->heaps);
		return (-1);
	}
	return (0);
}

int32_t	parse_user_input(char *input, uint16_t min, uint16_t max)
{
	uint16_t	result;

	result = 0;
	while (*input != '\0' && *input != '\n')
	{
		if (*input >= '0' && *input <= '9')
			result = result * 10 + (*input - '0');
		else
			return (INVALID_USER_INPUT);
		if (result > max || result < min)
			return (INVALID_USER_INPUT);
		input++;
	}
	return (result);
}
