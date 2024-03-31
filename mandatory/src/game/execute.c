/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:53 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/31 19:31:54 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	ft_putstr(playername);
	ft_putstr(" took ");
	ft_putu16(move);
	ft_putstr("\n");
	if (*heap == 0 && game->current_heap > 0)
		game->current_heap--;
	else if (game->current_heap == 0 && *heap == 0)
	{
		if (write(STDOUT_FILENO, playername, ft_strlen(playername)) == -1)
			return (-2);
		if (write(STDOUT_FILENO, " lost!\n", 7) == -1)
			return (-2);
	}
	return (0);
}

int32_t	execute_user_move(t_game *game)
{
	char		*input;
	uint16_t	move;
	int8_t		return_code;

	move = INVALID_USER_INPUT;
	while (move == INVALID_USER_INPUT)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			return (-1);
		move = parse_user_input(input, MIN_MOVE, MAX_MOVE);
		free(input);
		if (move == INVALID_USER_INPUT)
			print_error(INVALID_MOVE_ERROR);
		return_code = execute_move(game, move, "user");
		if (return_code == -1)
		{
			move = INVALID_USER_INPUT;
			print_error(MOVE_TOO_HIGH);
		}
		else if (return_code == -2)
			return (-1);
	}
	return (move);
}
