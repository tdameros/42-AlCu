/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:35:32 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/31 20:23:49 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	if (init_game(&game, fd) == -1)
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	if (start_game(&game) == -1)
	{
		print_error(GENERIC_ERROR);
		return (1);
	}
	vector_free(&game.heaps);
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
