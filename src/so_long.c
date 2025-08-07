/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:12:02 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/07 14:25:54 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*read_and_join_lines(int fd)
{
	char	*line;
	char	*joined;

	joined = NULL;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		joined = ft_strjoin_so_long(joined, line);
		if (!joined)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (joined);
}

/*char	**read_map_file(const char *file, t_game *game)
{
	int		fd;
	char	*joined;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		map_error(game, "Could not open the map");
	joined = read_and_join_lines(fd);
	close(fd);
	if (!joined)
		return (NULL);
	map = ft_split(joined, '\n');
	free(joined);
	if (!map)
		return (NULL);
	return (map);
}*/

char	**read_map_file(const char *file, t_game *game)
{
	int		fd;
	char	*joined;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		map_error(game, "Could not open the map");
	joined = read_and_join_lines(fd);
	close(fd);
	if (!joined || joined[0] == '\0')
	{
		free(joined);
		return (NULL);
	}
	map = ft_split(joined, '\n');
	free(joined);
	if (!map || !map[0] || map[0][0] == '\0')
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}

void	ft_init_game(t_game *game)
{
	game->mlx = mlx_init(game->width * TILE_SIZE,
			game->height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
		map_error(game, "Failed to initialize MLX");
	if (!load_images(game))
	{
		mlx_terminate(game->mlx);
		free_map(game->map);
		map_error(game, "Failed to load images");
	}
	locate_player(game);
}
int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		error_exit("Please, indicate one map.");
	ft_printf("check_extension\n");
	check_extension(av[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Failed to allocate memory for game.");
	game->map = NULL;
	ft_printf("reading map\n");
	game->map = read_map_file(av[1], game);
	if (game->map == NULL)
		map_error(game, "Map is empty or invalid.");
	ft_printf("map read successfully\n");
	game->width = get_map_width(game);
	game->height = get_map_height(game);
	ft_printf("width: %d, height: %d\n", game->width, game->height);
	if (game->width <= 0 || game->height <= 0)
		map_error(game, "Invalid map dimensions.");
	ft_printf("running check\n");
	check(game);
	ft_printf("running check_solvability\n");
	check_solvability(game);
	ft_printf("initializing game\n");
	ft_init_game(game);
	ft_printf("drawing map\n");
	draw_map(game);
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_close_hook(game->mlx, (void *)close_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map);
	free(game);
	cleanup_gnl();
	return (0);
}
/*int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		error_exit("Please, indicate one map.");
	check_extension(av[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Failed to allocate memory for game.");
	game->map = NULL;
	game->map = read_map_file(av[1], game);
	if (!(game->map))
		map_error(game, "Null map is prohibited");
	game->width = get_map_width(game);
	game->height = get_map_height(game);
	check(game);
	check_solvability(game);
	ft_init_game(game);
	draw_map(game);
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_close_hook(game->mlx, (void *)close_game, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map);
	free(game);
	cleanup_gnl();
	return (0);
}*/
