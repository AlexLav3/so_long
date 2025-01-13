/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:12:55 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/30 19:29:03 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_walkable(t_vars *vars, int x, int y)
{
	if (vars->map->copy[y][x] == '1' || vars->map->copy[y][x] == 'E')
		return (0);
	vars->is_moving = 1;
	return (1);
}

int	is_coll(t_vars *vars, int x, int y)
{
	if (vars->map->copy[y][x] == 'C')
		return (0);
	return (1);
}

int	is_exit(t_vars *vars)
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
			if (type == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	win_cond(t_vars *vars, int x, int y)
{
	if (vars->map->copy[y][x] == 'E' && count_coll(vars) == 0)
		return (1);
	return (0);
}

void	win(t_vars *vars, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	if (win_cond(vars, x + 1, y) || win_cond(vars, x - 1, y) || win_cond(vars,
			x, y + 1) || win_cond(vars, x, y - 1))
	{
		vars->can_move = 0;
		mlx_clear_window(vars->mlx, vars->win);
		mlx_string_put(vars->mlx, vars->win, screen_x, screen_y, 0xFFFA9E,
			"YOU WON");
		write(1, "🏆🏆YOU WON!!🏆🏆\n", 27);
		ft_close(vars);
	}
}
