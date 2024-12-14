/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:50:41 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/14 22:05:18 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_collect(t_vars *vars)
{
	int	a;

	a = TILE_SIZE;
	vars->collect = mlx_xpm_file_to_image(vars->mlx, "coll/coll1.xpm", &a, &a);
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
