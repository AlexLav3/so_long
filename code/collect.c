/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:50:41 by elavrich          #+#    #+#             */
/*   Updated: 2025/01/05 19:38:46 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_collect(t_vars *vars)
{
	int		a;
	int		x;
	int		y;
	char	type;

	a = TILE_SIZE;
	y = 0;
	while (y < vars->map->y)
	{
		x = 0;
		while (x < vars->map->x)
		{
			type = vars->map->copy[y][x];
			if (type == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->collect, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	collect(t_vars *vars, int x, int y)
{
	int	count;
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	count = count_coll(vars);
	if (is_coll(vars, x + 1, y))
	{
		vars->map->copy[y][x] = '0';
	}
	load_map(vars);
}

int	count_coll(t_vars *vars)
{
	int	x;
	int	y;
	int	type;
	int	count;

	count = 0;
	y = 0;
	while (y < vars->map->y)
	{
		x = 0;
		while (x < vars->map->x)
		{
			type = vars->map->copy[y][x];
			if (type == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	update_animation(t_animation *animation, t_vars *vars, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	if (vars->is_closed || !animation)
		return (0);
	load_map(vars);
	load_frame(animation, vars, x, y);
	return (0);
}

void	populate_map(t_map *map)
{
	int	fd;
	int	y;

	y = 0;
	fd = open(map->image_file, O_RDONLY);
	if (fd < 0)
		return (free(map->copy));
	while (y < map->count)
	{
		map->copy[y] = get_next_line(fd);
		if (!map->copy[y])
		{
			while (--y >= 0)
				free(map->copy[y]);
			free(map->copy);
			map->copy = NULL;
			close(fd);
			return ;
		}
		y++;
	}
	map->copy[y++] = NULL;
	close(fd);
}
