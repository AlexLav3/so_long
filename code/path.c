/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:24:41 by elavrich          #+#    #+#             */
/*   Updated: 2025/01/05 23:41:59 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill(char **copy, int x, int y, int **visited)
{
	if (y < 0 || x < 0 || !copy[y] || copy[y][x] == '1' || visited[y][x] == 1)
		return (0);
	visited[y][x] = 1;
	fill(copy, x + 1, y, visited);
	fill(copy, x, y + 1, visited);
	fill(copy, x - 1, y, visited);
	fill(copy, x, y - 1, visited);
	return (1);
}

int	check_path(t_vars *vars)
{
	int	x;
	int	y;
	int	**visited;
	int	i;

	visited = make_vis(vars);
	y = 0;
	while (vars->map->copy[y])
	{
		x = 0;
		while (vars->map->copy[y][x])
		{
			find_player(vars, y, x);
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
	if (!use_fill(vars, visited))
		return (0);
	return (1);
}

int	use_fill(t_vars *vars, int **visited)
{
	int	y;
	int	x;

	x = 0;
	fill(vars->map->copy, vars->player_x, vars->player_y, visited);
	y = 0;
	while (vars->map->copy[y])
	{
		x = 0;
		while (vars->map->copy[y][x])
		{
			if ((vars->map->copy[y][x] == 'C' || vars->map->copy[y][x] == 'E')
				&& visited[y][x] == 0)
			{
				return (0);
			}
			x++;
		}
		y++;
	}
	clean_vis(visited, vars->window_height);
	return (1);
}

void	find_player(t_vars *vars, int y, int x)
{
	if (vars->map->copy[y][x] == 'P')
	{
		vars->player_x = x;
		vars->player_y = y;
	}
}

int	**make_vis(t_vars *vars)
{
	int	i;
	int	**visited;

	i = 0;
	visited = (int **)malloc(sizeof(int *) * vars->window_height);
	while (i < vars->window_height)
	{
		visited[i] = (int *)malloc(sizeof(int) * vars->window_width);
		i++;
	}
	return (visited);
}
