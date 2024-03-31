#ifndef WINDOW_H
# define WINDOW_H

# include "game.h"

# define GAME_TITLE "Nim Game"
# define USER_PROMPT "Enter a move (1-%d): "
# define ANY_TO_EXIT "Press any key to exit"
# define LINE_TOO_LONG "Line too long"
# define HEAP_SIDEBAR_REQUIRE 10
# define STICK_SPACE 2
# define HEAP_SPACE 2
# define FOOTER_SPACE 3
# define HEADER_SPACE 2
# define SIDEBAR_SPACE 2


typedef struct s_gui
{
    size_t	scroll_offset;
	bool	scroll_enabled;
    uint8_t	highlight_amount;
}	t_gui;

int	create_game_window(t_game *game, t_ai *ai);

#endif