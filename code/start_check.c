/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:24:11 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/17 00:10:44 by elavrich         ###   ########.fr       */
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
	if (!check_map(vars))
	{
		ft_printf("invalid map\n");
		return (ft_close(vars), 0);
	}
	init_collect(vars);
	map_y_x(vars);
	set_map(vars);
	load_map(vars);
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
void	clean_vars(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map->floor)
		mlx_destroy_image(vars->mlx, vars->map->floor);
	if (vars->map->wall1)
		mlx_destroy_image(vars->mlx, vars->map->wall1);
	if (vars->map->exit)
		mlx_destroy_image(vars->mlx, vars->map->exit);
	if (vars->collect)
		mlx_destroy_image(vars->mlx, vars->collect);
	if (vars->map->copy)
	{
		while (vars->map->copy[i])
		{
			free(vars->map->copy[i]);
			i++;
		}
		free(vars->map->copy);
	}
}
