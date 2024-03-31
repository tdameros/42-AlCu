#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "window.h"
#include "game.h"
#include "error.h"

static int	get_fd(int argc, char **argv);

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;
	t_ai	ai;

	fd = get_fd(argc, argv);
	if (fd == -1)
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	if (init_game(&game, fd) == -1)
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	printf("Start game\n");
	if (init_ai(&game, &ai) == -1)
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	create_game_window(&game, &ai);
	vector_free(&game.heaps);
	free(ai.should_start);
	return (0);
}

static int	get_fd(int argc, char **argv)
{
	int	fd;

	fd = STDIN_FILENO;
	if (argc >= 3)
		return (-1);
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
