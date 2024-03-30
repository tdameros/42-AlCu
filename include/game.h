/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:36:55 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/29 23:36:56 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

# include "vector.h"

# define HEAP_MAX_ITEMS 10000
# define HEAP_MIN_ITEMS 1
# define MAX_MOVE 3
# define MIN_MOVE 1
# define INVALID_USER_INPUT 0

typedef struct s_game
{
	size_t		current_heap;
	t_vector	heaps;
}	t_game;

typedef struct s_ai
{
	bool	*should_start;
}	t_ai;

int			parse(t_game *game, int fd);
int32_t		init_game(t_game *game, int fd);
void		start_game(t_game *game);
int32_t		parse_user_input(char *input, uint16_t min, uint16_t max);
void		display_game(t_game *game);

int8_t		execute_move(t_game *game, uint16_t move, char *playername);
int32_t		execute_user_move(t_game *game);
uint16_t	*get_heap(t_game *game, size_t heap_index);

int16_t		init_ai(t_game *game, t_ai *ai);
uint16_t	get_ai_move(t_game *game, t_ai *ai);

#endif
