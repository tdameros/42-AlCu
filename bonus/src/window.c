#include <ncurses.h>

#include "game.h"
#include "parsing/get_next_line.h"
#include "window.h"
#include "error.h"

static void		display_game_ncurses(t_game *game, t_gui *gui);
static void		display_rows(t_game *game, t_gui *gui);
static void		game_over(bool is_last_player);
static void		wait_any_user_input(void);
static int 		get_key();

int8_t	await_user_input(t_game *game, t_gui *gui);

int	create_game_window(t_game *game, t_ai *ai)
{
	bool		is_last_player;
	uint16_t	ai_move;
	t_gui		gui;

	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	is_last_player = false;
	gui.scroll_offset = 0;
	while (!is_finished(game))
	{
		ai_move = get_ai_move(game, ai);
		gui.highlight_amount = ai_move;
		clear();
		display_game_ncurses(game, &gui);
		refresh();
		wait_any_user_input();
		execute_move(game, ai_move);
		gui.highlight_amount = 0;
		is_last_player = false;
		if (is_finished(game))
			break ;
		clear();
		display_game_ncurses(game, &gui);
		refresh();
		await_user_input(game, &gui);
		is_last_player = true;
	}
	game_over(is_last_player);
	endwin();
	curs_set(1);
	return 0;
}

static	void	wait_any_user_input(void)
{
	timeout(500);
	get_key();
	timeout(-1);
}

static void	game_over(bool is_last_player)
{
	clear();
	if (!is_last_player)
	{
		if (COLS < 52 || LINES < 7)
			mvprintw(LINES / 2, (COLS - 25) / 2, "You won! Congratulations!");
		else
		{
			mvprintw(LINES / 2 - 3, (COLS - 52) / 2, 	"   __  _______ __________     _       ______  _   __");
			mvprintw(LINES / 2 - 2, (COLS - 52) / 2, 	"  / / / / ___// ____/ __ \\   | |     / / __ \\/ | / /");
			mvprintw(LINES / 2 - 1, (COLS - 52) / 2, 	" / / / /\\__ \\/ __/ / /_/ /   | | /| / / / / /  |/ / ");
			mvprintw(LINES / 2, (COLS - 52) / 2, 		"/ /_/ /___/ / /___/ _, _/    | |/ |/ / /_/ / /|  /  ");
			mvprintw(LINES / 2 + 1, (COLS - 52) / 2, 	"\\____//____/_____/_/ |_|     |__/|__/\\____/_/ |_/   ");
		}
	}
	else
	{
		if (COLS < 40 || LINES < 7)
			mvprintw(LINES / 2, (COLS - 9) / 2, "You lost!");
		else
		{
			mvprintw(LINES / 2 - 3, (COLS - 40) / 2,	"    ___    ____   _       ______  _   __");
			mvprintw(LINES / 2 - 2, (COLS - 40) / 2, 	"   /   |  /  _/  | |     / / __ \\/ | / /");
			mvprintw(LINES / 2 - 1, (COLS - 40) / 2, 	"  / /| |  / /    | | /| / / / / /  |/ / ");
			mvprintw(LINES / 2, (COLS - 40) / 2, 		" / ___ |_/ /     | |/ |/ / /_/ / /|  /  ");
			mvprintw(LINES / 2 + 1, (COLS - 40) / 2, 	"/_/  |_/___/     |__/|__/\\____/_/ |_/   ");
		}
	}
	mvprintw(LINES - 2, (COLS - ft_strlen(ANY_TO_EXIT)) / 2, ANY_TO_EXIT);
	refresh();
	cbreak();
	getch();
}

static int get_key()
{
	int input = getch();
	if (input == '\033')
	{
		getch();
		switch (getch())
		{
		case 'A': return (KEY_UP);
		case 'B': return (KEY_DOWN);
		case 'C': return (KEY_RIGHT);
		case 'D': return (KEY_LEFT);
		}
	}
	return (input);
}

int8_t	await_user_input(t_game *game, t_gui *gui)
{
	int			ch;
	uint16_t	move;
	int8_t		ret;
	uint16_t	max_move;
	char		*err;

	move =  0;
	err = "";
	while (1)
	{
		if (!gui->scroll_enabled)
			gui->scroll_offset = 0;
		clear();
		display_game_ncurses(game, gui);
		max_move = *get_heap(game, game->current_heap);
		if (max_move > 3)
			max_move = 3;
		mvprintw(LINES - 2, (COLS - ft_strlen(USER_PROMPT)) / 2, USER_PROMPT, max_move);
		mvprintw(LINES - 1, (COLS - ft_strlen(err)) / 2, "%s", err);
		refresh();
		cbreak();
		ch = get_key();
		nocbreak();
		if (ch == '1' || ch == '2' || ch == '3')
		{
			move = ch - '0';
			ret = execute_move(game, move);
			if (ret != -1)
				break;
			err = MOVE_TOO_HIGH;
		}
		else if (ch == KEY_UP)
		{
			if (gui->scroll_offset < game->heaps.len - 2 && gui->scroll_enabled)
				gui->scroll_offset++;
		}
		else if (ch == KEY_DOWN)
		{
			if (gui->scroll_offset > 0 && gui->scroll_enabled)
				gui->scroll_offset--;
		}
		else
			err = MOVE_TOO_HIGH;
	}
	gui->scroll_offset = 0;
	return (ret);
}

static void    display_game_ncurses(t_game *game, t_gui *gui)
{
    int maxY, maxX;
    (void) maxY;
    (void) maxX;
    (void) game;
    getmaxyx(stdscr, maxY, maxX);
    mvprintw(0, (maxX - ft_strlen(GAME_TITLE)) / 2 , GAME_TITLE);
	display_rows(game, gui);
}

static void     display_rows(t_game *game, t_gui *gui)
{
	uint32_t body = LINES - FOOTER_SPACE - HEADER_SPACE;
	uint32_t bottom_heap = game->current_heap - gui->scroll_offset;
	uint32_t nb_element_display = 0;
	uint32_t max_column = 0;
	if (body / HEAP_SPACE < game->current_heap) {
		gui->scroll_enabled = true;
	} else {

		gui->scroll_enabled = false;
	}
	if (body / HEAP_SPACE < bottom_heap) {
		nb_element_display = body / HEAP_SPACE;
	} else {
		nb_element_display = bottom_heap;
	}
    uint32_t	last_body_row = LINES - 1 - FOOTER_SPACE;
	uint32_t	center_body_row = (body - (nb_element_display) * HEAP_SPACE) / 2;
	uint32_t	row = 0;
	if (gui->scroll_offset != 0) {
		row = last_body_row - 1;
	} else {
		row = last_body_row - center_body_row;
	}
    for (ssize_t i = bottom_heap; i >= 0; i--) {
        uint16_t	heap = *get_heap(game, i);
		uint32_t	column = (COLS - heap * STICK_SPACE) / 2;
		if (heap * STICK_SPACE + HEAP_SIDEBAR_REQUIRE >= COLS) {
			mvprintw(row, (COLS - ft_strlen(LINE_TOO_LONG)) / 2, LINE_TOO_LONG);
			column = ((COLS - ft_strlen(LINE_TOO_LONG)) / 2) + ft_strlen(LINE_TOO_LONG);
		} else {
			for (size_t j = 0; j < heap; j++) {
				column += STICK_SPACE;
				if ((size_t)i == game->current_heap && j >= (size_t)(heap - gui->highlight_amount)) {
					attron(COLOR_PAIR(1));
					mvprintw(row, column, "|");
					attroff(COLOR_PAIR(1));
				} else {
					mvprintw(row, column, "|");
				}
			}
		}
		if (column > max_column)
			max_column = column;
		row -= HEAP_SPACE;
		if (row <= HEADER_SPACE) {
			mvprintw(row, (COLS - 3) / 2, "...");
			break;
		}
    }
	if (gui->scroll_offset != 0) {
		row = last_body_row - 1;
	} else {
		row = last_body_row - center_body_row;
	}
	for (int32_t i = bottom_heap; i >= 0; i--) {
        uint16_t	heap = *get_heap(game, i);
		mvprintw(row, max_column + SIDEBAR_SPACE, "(%d)", heap);
		row -= HEAP_SPACE;
		if (row <= HEADER_SPACE)
			break;
	}
}