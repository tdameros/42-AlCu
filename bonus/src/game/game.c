/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:50 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/31 20:07:12 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "game.h"
#include "error.h"
#include "parsing/get_next_line.h"

int32_t	init_game(t_game *game, int fd)
{
	if (parse(game, fd) != 0)
		return (-1);
	game->current_heap = game->heaps.len - 1;
	return (0);
}

void	start_game(t_game *game)
{
	t_ai	ai;

	if (init_ai(game, &ai) == -1)
		return ;
	while (!is_finished(game))
	{
		display_game(game);
		execute_move(game, get_ai_move(game, &ai));
		if (is_finished(game))
			break ;
		display_game(game);
		if (execute_user_move(game) == -1)
			break ;
	}
	free(ai.should_start);
}

void	display_game(t_game *game)
{
	u_int32_t	index;

	index = 0;
	while (index < game->heaps.len)
	{
		if (*get_heap(game, index) != 0)
			printf("%d\n", *get_heap(game, index));
		index++;
	}
	printf("----------------------\n");
}

bool	is_finished(t_game *game)
{
	return (game->current_heap == 0 && *get_heap(game, 0) == 0);
}

uint16_t	*get_heap(t_game *game, size_t heap_index)
{
	return (((uint16_t *)game->heaps.tab) + heap_index);
}
