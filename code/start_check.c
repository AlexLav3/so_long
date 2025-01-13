/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:24:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/01/05 23:41:06 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_vars *vars, t_animation *animation, t_map *map, char **argv)
{
	int	exit;

	vars->is_moving = 0;
	vars->moves = 0;
	vars->can_move = 1;
	map->image_file = argv[1];
	inizialize_map(map);
	vars->map = map;
	set_map(vars);
	if (!check_map(vars) || !check_path(vars) || !invalid_char(vars))
	{
		ft_printf("invalid map\n");
		return (0);
	}
	vars->win = mlx_new_window(vars->mlx, vars->window_width,
			vars->window_height, "so_long");
	load_map(vars);
	init_collect(vars);
	exit = is_exit(vars);
	if (exit != 1 || count_coll(vars) < 1)
		return (ft_printf("invalid map\n"), ft_close(vars), 0);
	animation->direction = 1;
	set_frames(animation, vars);
	set_frames_u_d(animation, vars);
	return (find_pos(vars, animation), 1);
}

int	check_map(t_vars *vars)
{
	int	rows;
	int	columns;
	int	col;
	int	row;

	get_map_dimensions(vars, &rows, &columns);
	col = 0;
	while (col < columns)
	{
		if (vars->map->copy[0][col] != '1' || vars->map->copy[rows
			- 1][col] != '1')
			return (0);
		col++;
	}
	row = 0;
	while (row < rows)
	{
		if (vars->map->copy[row][0] != '1' || vars->map->copy[row][columns
			- 1] != '1')
			return (0);
		row++;
	}
	return (1);
}

void	clean(t_vars *vars, t_animation *animation)
{
	int	i;

	if (!animation)
		return ;
	i = 0;
	while (i < 13)
	{
		if (animation->img[i])
		{
			mlx_destroy_image(vars->mlx, animation->img[i]);
			free(animation->img[i]);
		}
		i++;
	}
}

void	clean_vis(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	map_y_x(t_vars *vars)
{
	int	x;
	int	y;
	int	max_width;

	if (vars->map->copy == NULL)
		return ;
	y = 0;
	max_width = 0;
	while (vars->map->copy[y])
	{
		x = 0;
		while (vars->map->copy[y][x])
			x++;
		if (x > max_width)
			max_width = x;
		y++;
	}
	vars->map->x = max_width;
	vars->map->y = y;
}
