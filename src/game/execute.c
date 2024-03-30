/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:53 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/30 01:19:53 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "parsing/get_next_line.h"
#include "game.h"
#include "error.h"

int8_t	execute_move(t_game *game, uint16_t move, char *playername)
{
	uint16_t	*heap;

	heap = get_heap(game, game->current_heap);
	if (*heap < move)
		return (-1);
	*heap -= move;
	if (*heap == 0 && game->current_heap > 0)
		game->current_heap--;
	else if (game->current_heap == 0 && *heap == 0)
	{
		write(STDOUT_FILENO, playername, ft_strlen(playername));
		write(STDOUT_FILENO, " lost!\n", 7);
	}
	return (0);
}

int32_t	execute_user_move(t_game *game)
{
	char		*input;
	uint16_t	move;

	move = INVALID_USER_INPUT;
	while (move == INVALID_USER_INPUT)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			return (-1);
		move = parse_user_input(input, MIN_MOVE, MAX_MOVE);
		if (move == INVALID_USER_INPUT)
			print_error(INVALID_MOVE_ERROR);
		if (execute_move(game, move, "user") == -1)
		{
			move = INVALID_USER_INPUT;
			print_error(MOVE_TOO_HIGH);
		}
		free(input);
	}
	return (move);
}