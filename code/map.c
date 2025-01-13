/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:47:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/01/13 21:12:35 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_map(t_vars *vars)
{
	int	a;

	map_y_x(vars);
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

void	inizialize_map(t_map *map)
{
	int		fd;
	char	*line;
	int		count;
	int		y;

	count = 0;
	y = 0;
	fd = open(map->image_file, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->count = count;
	map->copy = malloc((count + 1) * sizeof(char *));
	if (!map->copy)
		return ;
	populate_map(map);
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
				change_sprite(animation);
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
		*columns = ft_strlen(vars->map->copy[0]) - 1;
	else
		*columns = 0;
	vars->window_height = *rows * TILE_SIZE;
	vars->window_width = *columns * TILE_SIZE;
	if (vars->window_height == vars->window_width)
		return (1);
	return (0);
}
