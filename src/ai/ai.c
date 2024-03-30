/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:57 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/30 01:19:58 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "game.h"

static bool	start_condition(uint16_t heap);
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
	printf("0 = %d\n", ai->should_start[0]);
	i = 1;
	while (i < game->heaps.len)
	{
		should_start_next = ai->should_start[i - 1];
		if (start_condition(*get_heap(game, i)))
			ai->should_start[i] = should_start_next;
		else
			ai->should_start[i] = !should_start_next;
		printf("%lu = %d\n", i, ai->should_start[i]);
		i++;
	}
	return (0);
}

static bool	start_condition(uint16_t heap)
{
	return (heap <= 3 && heap != 1) || (heap % 4 != 1 && heap > 3);
}

uint16_t	get_ai_move(t_game *game, t_ai *ai)
{
	uint16_t	heap = *get_heap(game, game->current_heap);

	if (game->current_heap == 0 || ai->should_start[game->current_heap - 1])
		printf("AI SHOULD WIN\n");
	else
		printf("AI SHOULD LOSE\n");
	if (game->current_heap == 0 || ai->should_start[game->current_heap - 1])
		return (get_heap_win_move(heap));
	return (get_heap_lose_move(heap));
}

static uint16_t	get_heap_win_move(uint16_t heap)
{
	if (heap == 1)
		return (1);
	if (heap <= 4)
		return (heap - 1);
	if (heap % 4 == 1)
		return (2);
	if (heap % 4 == 0)
		return ((4 - (heap % 4)) - 1);
	return (heap % 4 - 1);
}

static uint16_t	get_heap_lose_move(uint16_t heap)
{
	if (heap <= 3)
		return (heap);
	if (heap % 3 == 1)
		return (2);
	if (heap % 3 == 0)
		return ((3 - (heap % 3)) - 1);
	return (heap % 3 - 1);
}