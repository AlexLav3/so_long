/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:47:49 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/22 19:10:59 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_map(t_vars *vars)
{
	int	a;

	a = TILE_SIZE;
	vars->map->floor = mlx_xpm_file_to_image(vars->mlx, "map/floor.xpm", &a,
			&a);
	vars->map->wall1 = mlx_xpm_file_to_image(vars->mlx, "map/wall1.xpm", &a,
			&a);
	vars->map->exit = mlx_xpm_file_to_image(vars->mlx, "map/exit.xpm", &a, &a);
	vars->collect = mlx_xpm_file_to_image(vars->mlx, "coll/coll1.xpm", &a, &a);
}

void	load_map(t_vars *vars)
{
	int		x;
	int		y;
	char	type;

	y = 0;
	while (y < vars->map->y)
	{
		x = 0;
		while (x < vars->map->x)
		{
			type = vars->map->copy[y][x];
			if (type == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->map->floor,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (type == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->map->wall1,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (type == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->map->exit, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
//ft_split returns **char, that is why we are reading,
//joining and splitting again.
//we need ** for the copy to be able to itinerate through the map with [x][y]

void	inizialize_map(t_map *map)
{
	int		fd;
	char	*line;

	map->file = malloc(1);
	map->file[0] = '\0';
	fd = open(map->image_file, O_RDONLY);
	if (fd < 0 || !map->file)
		return (free(map->file));
	line = get_next_line(fd);
	while (line)
	{
		map->file = ft_strjoin_g(map->file, line);
		free(line);
		line = get_next_line(fd);
	}
	if (map->file)
	{
		map->copy = ft_split(map->file, '\n');
		if (!map->copy)
			map->file = NULL;
	}
	else
		map->copy = NULL;
	close(fd);
}

void	find_pos(t_vars *vars, t_animation *animation)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (vars->map->copy[y])
	{
		x = 0;
		while (vars->map->copy[y][x])
		{
			if (vars->map->copy[y][x] == 'P')
			{
				vars->map->copy[y][x] = '0';
				vars->player_x = x;
				vars->player_y = y;
				change_sprite(animation, vars);
				load_frame(animation, vars, vars->player_x, vars->player_y);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	get_map_dimensions(t_vars *vars, int *rows, int *columns)
{
	*rows = 0;
	while (vars->map->copy[*rows] != NULL)
		(*rows)++;
	if (*rows > 0)
		*columns = ft_strlen(vars->map->copy[0]);
	else
		*columns = 0;
	return (0);
}
