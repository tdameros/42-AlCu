/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:57 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/31 18:46:48 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "game.h"

static bool		start_condition(uint16_t heap);
static uint16_t	get_heap_lose_move(uint16_t heap);
static uint16_t	get_heap_win_move(uint16_t heap);

int16_t	init_ai(t_game *game, t_ai *ai)
{
	size_t	i;
	bool	should_start_next;

	ai->should_start = malloc(sizeof(*ai->should_start) * game->heaps.len);
	if (ai->should_start == NULL)
		return (-1);
	ai->should_start[0] = start_condition(*get_heap(game, 0));
	i = 1;
	while (i < game->heaps.len)
	{
		should_start_next = ai->should_start[i - 1];
		if (!should_start_next)
			ai->should_start[i] = *get_heap(game, i) % 4 != 0;
		else
			ai->should_start[i] = start_condition(*get_heap(game, i));
		i++;
	}
	return (0);
}

static bool	start_condition(uint16_t heap)
{
	return (heap % 4 != 1);
}

uint16_t	get_ai_move(t_game *game, const t_ai *ai)
{
	uint16_t	heap;

	heap = *get_heap(game, game->current_heap);
	if (game->current_heap == 0 || ai->should_start[game->current_heap - 1])
		return (get_heap_win_move(heap));
	return (get_heap_lose_move(heap));
}

static uint16_t	get_heap_win_move(uint16_t heap)
{
	if ((heap - 1) % 4 == 0)
		return (1);
	return ((heap - 1) % 4);
}

static uint16_t	get_heap_lose_move(uint16_t heap)
{
	if (heap % 4 == 0)
		return (1);
	return (heap % 4);
}
